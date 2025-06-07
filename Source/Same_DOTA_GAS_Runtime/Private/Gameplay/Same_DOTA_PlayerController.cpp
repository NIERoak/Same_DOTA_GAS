// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Same_DOTA_PlayerController.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "Net/UnrealNetwork.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"

#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "Engine/LocalPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"




#define ECC_PluginCustomObject ECC_Selected_Unit


//注册需要网络复制的变量
void ASame_DOTA_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ASame_DOTA_PlayerController, PC_TeamID, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ASame_DOTA_PlayerController, PC_PlayerID, COND_None, REPNOTIFY_Always);

}

ASame_DOTA_PlayerController::ASame_DOTA_PlayerController()
{
	
	bOnMouseDrag = false;
		
}



void ASame_DOTA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	MyHUD_Ref = Cast<ASame_DOTA_HUD>(GetHUD());
	MyCameraPawn_Ref = Cast<ASame_DOTA_CameraPawn>(GetPawn());
	
	
}

void ASame_DOTA_PlayerController::GetMouseHitResultByChannal()
{
	FHitResult HitResult;
	bool bHit = GetHitResultUnderCursorByChannel(
		TraceTypeQuery1,  // 检测的碰撞通道（如可见性、物理体等）
		false,                              // 是否忽略复杂碰撞（通常为 false）
		HitResult                           // 输出命中结果
	);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) {
			
			MouseHitActor = HitActor;			
			
		}
		MouseHitLocation = HitResult.Location;
		
	}
	
}

void ASame_DOTA_PlayerController::SelectUnits()
{
	if (MyHUD_Ref)
	{		
		FVector PointEnter{ ((StartLocation.X+ EndLocation .X)/2),((StartLocation.Y + EndLocation.Y) / 2) ,((StartLocation.Z + EndLocation.Z) / 2) };
		FVector BoxHalfSize{ FMath::Abs((StartLocation.X - EndLocation.X) / 2),FMath::Abs((StartLocation.Y - EndLocation.Y) / 2) ,100.0f };

		FVector StartPointlocation{ PointEnter.X,PointEnter.Y,PointEnter.Z + 300.0f };
		FVector EndPointLocation{ PointEnter.X,PointEnter.Y,PointEnter.Z - 300.0f };
				
		TArray<AActor*> ActorsToIgnore;		
		TArray<FHitResult> OutHits;
		const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(Unit) };

		const bool bHit=UKismetSystemLibrary::BoxTraceMultiForObjects(
			GetWorld(), 
			StartPointlocation, 
			EndPointLocation, 
			BoxHalfSize,
			FRotator::ZeroRotator,
			ObjectTypes, 
			false, 
			ActorsToIgnore, 
			EDrawDebugTrace::None,
			OutHits,
			true, 
			FColor::Green, 
			FColor::Red,
			0.0f);		
		
		if (bHit)
		{
			if (!Selected_UnitsSelf.IsEmpty() || Selected_UnitFriend != nullptr || Selected_UnitEnemy != nullptr)
			{
				for (AActor* OldActor : Selected_UnitsSelf)
				{
					if (ASame_DOTA_CharacterBase* OldSelectedActor = Cast<ASame_DOTA_CharacterBase>(OldActor))
					{
						OldSelectedActor->SetSelectedRingVisibility(false);//让选择框不可视
					}
				}
				if (ASame_DOTA_CharacterBase* OldSelectedActor = Cast<ASame_DOTA_CharacterBase>(Selected_UnitFriend))
				{
					OldSelectedActor->SetSelectedRingVisibility(false);//让选择框不可视
				}
				if (ASame_DOTA_CharacterBase* OldSelectedActor = Cast<ASame_DOTA_CharacterBase>(Selected_UnitEnemy))
				{
					OldSelectedActor->SetSelectedRingVisibility(false);//让选择框不可视
				}				
			}
			
			Selected_UnitsSelf.Empty();
			Selected_UnitFriend = nullptr;
			Selected_UnitEnemy = nullptr;

			


			bool bSelectedSelfUnits = false;

			for (const FHitResult& Hit : OutHits)
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor)
				{
					
					if (ASame_DOTA_CharacterBase* SelectedActor = Cast<ASame_DOTA_CharacterBase>(HitActor))
					{
						if (!SelectedActor->bDeath && SelectedActor->Char_PlayerID == PC_PlayerID)
						{
							SelectedActor->SetSelectedRingVisibility(true);//让选择框可视
							Selected_UnitsSelf.Add(SelectedActor);
							bSelectedSelfUnits = true;
							//实现单位被框选后的函数
							MyHUD_Ref->UpdateMainMenu();//更新一次主菜单
						}
					}		
				}
			}

			if (!bSelectedSelfUnits)
			{
				for (const FHitResult& Hit : OutHits)
				{
					AActor* HitActor = Hit.GetActor();
					if (ASame_DOTA_CharacterBase* SelectedActor = Cast<ASame_DOTA_CharacterBase>(HitActor)) 
					{
						if (!SelectedActor->bDeath && SelectedActor->Char_TeamID == PC_TeamID)
					    {
						Selected_UnitFriend = SelectedActor;
						SelectedActor->SetSelectedRingVisibility(true);//让选择框可视
						//实现单位被框选后的函数
						MyHUD_Ref->UpdateMainMenu();//更新一次主菜单
						
						
						break;
					    }
						else
						{
							if (!SelectedActor->bDeath) {

								Selected_UnitEnemy = SelectedActor;
								SelectedActor->SetSelectedRingVisibility(true);//让选择框可视							

							};

							MyHUD_Ref->UpdateMainMenu();//更新一次主菜单
							break;
						}
					 
					}
					
					
				}
			}
		}		
	}
}

//设置队伍和玩家ID
void ASame_DOTA_PlayerController::Server_SetPCTeamIDandPlayerID_Implementation(ETeamID InTeamID, EPlayerID InPlayerID)
{
	PC_TeamID = InTeamID;
	PC_PlayerID = InPlayerID;
}

bool ASame_DOTA_PlayerController::Server_SetPCTeamIDandPlayerID_Validate(ETeamID InTeamID, EPlayerID InPlayerID)
{
	return true;
}


FVector ASame_DOTA_PlayerController::MouseEdgeMove(float ScreenSizeRate, FVector HorizontalIncrease, FVector HorizontalDecreasing, FVector VerticalIncrease, FVector VerticalDecreasing)
{
	FVector MouseLocation;
	bool bHaveMouse;
	FVector2D ViewportSize;
	bHaveMouse = GetMousePosition(MouseLocation.X, MouseLocation.Y);
	
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	float RateX = MouseLocation.X / ViewportSize.X;
	float RateY = MouseLocation.Y / ViewportSize.Y;

	FVector SelectedVector{0.f,0.f,0.f};


	if (RateX>=1- ScreenSizeRate)
	{
		bool bSelectA=true;	
		
		SelectedVector = UKismetMathLibrary::SelectVector(HorizontalIncrease, {0.f,0.f,0.f}, bSelectA);
	
	}
	if (RateX <=ScreenSizeRate)
	{
		bool bSelectA = true;

		SelectedVector = UKismetMathLibrary::SelectVector(HorizontalDecreasing, { 0.f,0.f,0.f }, bSelectA);

	}
	if (RateY >= 1 - ScreenSizeRate)
	{
		bool bSelectA = true;

		SelectedVector = UKismetMathLibrary::SelectVector(VerticalDecreasing, { 0.f,0.f,0.f }, bSelectA);

	}
	if (RateY <= ScreenSizeRate)
	{
		bool bSelectA = true;

		SelectedVector = UKismetMathLibrary::SelectVector(VerticalIncrease, { 0.f,0.f,0.f }, bSelectA);

	}
		
	return SelectedVector;
}

void ASame_DOTA_PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MouseLeftMappingContext, 0);
	}
		
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		//绑定鼠标左键点击事件
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnMouseLeftClikInputStarted);
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Triggered, this, &ASame_DOTA_PlayerController::OnMouseLeftClikTriggered);
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Completed, this, &ASame_DOTA_PlayerController::OnMouseLeftClikReleased);
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Canceled, this, &ASame_DOTA_PlayerController::OnMouseLeftClikReleased);
		//绑定鼠标右键点击事件
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnMouseRightClikInputStarted);
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Triggered, this, &ASame_DOTA_PlayerController::OnMouseRightClikTriggered);
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Completed, this, &ASame_DOTA_PlayerController::OnMouseRightClikReleased);
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Canceled, this, &ASame_DOTA_PlayerController::OnMouseRightClikReleased);
		
		//释放技能按键
		EnhancedInputComponent->BindAction(ReleaseSkill_1, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_1Started);
		EnhancedInputComponent->BindAction(ReleaseSkill_2, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_2Started);
		EnhancedInputComponent->BindAction(ReleaseSkill_3, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_3Started);
		EnhancedInputComponent->BindAction(ReleaseSkill_4, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_4Started);

		//自由攻击移动按键
		EnhancedInputComponent->BindAction(UnitFreedomAttackMoveAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnUnitFreedomAttackMoveStarted);
		
		//巡逻
		EnhancedInputComponent->BindAction(UnitPatrolAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnUnitPatrolStarted);
		EnhancedInputComponent->BindAction(UnitPatrolAction, ETriggerEvent::Completed, this, &ASame_DOTA_PlayerController::OnUnitPatrolReleased);
	}
}

//开始触发一次
void ASame_DOTA_PlayerController::OnMouseLeftClikInputStarted()
{
	GetMouseHitResultByChannal();
	StartLocation = MouseHitLocation;
	
	if (bPrFreedomAttacking)
	{
		
		bool bHitActor = false;
		for (TObjectPtr<AActor> UnitPtr : Selected_UnitsSelf)
		{
			if (UnitPtr)
			{
				if (MouseHitActor != nullptr)
				{
					if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(MouseHitActor))
					{
						MyCameraPawn_Ref->UnitBaseMoveToLocation(UnitPtr, EndLocation, NewChar);
						bHitActor = true;
					}
					else
					{

						//开启自由攻击移动到位置
						for (AActor* SeletedUnitSelf : Selected_UnitsSelf)
						{
							MyCameraPawn_Ref->UnitFreedomAttackMoveToLocation(SeletedUnitSelf, StartLocation, true);
						}
						
					}
				}
				else
				{					
					//开启自由攻击移动到位置
					for (AActor* SeletedUnitSelf : Selected_UnitsSelf)
					{
						MyCameraPawn_Ref->UnitFreedomAttackMoveToLocation(SeletedUnitSelf, StartLocation, true);
					}
				}
			}
		}
		if (bHitActor != true)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor_Attack, StartLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
		
	}
	else if (bPrePatrol)
	{
		PatrolPoints.AddUnique(MouseHitLocation);		
	}	
	else if(bPreReleaseSkill)
	{
		//技能释放逻辑
	}
	else
	{
		//存储鼠标第一次点击的位置
		bOnMouseDrag = true;//鼠标按下
		
	}	
}

//触发期间持续触发
void ASame_DOTA_PlayerController::OnMouseLeftClikTriggered()
{
	if (!bPrFreedomAttacking && !bPrePatrol && !bPreReleaseSkill)
	{
		//在屏幕绘画方框
		if (MyHUD_Ref)
		{
			MyHUD_Ref->StartDrawBoxOnScreen(bOnMouseDrag, StartLocation);
		}
	}
}
	
//触发结束
void ASame_DOTA_PlayerController::OnMouseLeftClikReleased()
{
	if (!bPrFreedomAttacking)
	{
		bOnMouseDrag = false;//鼠标松开

		GetMouseHitResultByChannal();
		EndLocation = MouseHitLocation;

		if (MyHUD_Ref)
		{

			MyHUD_Ref->StartDrawBoxOnScreen(bOnMouseDrag, StartLocation);
		}
		SelectUnits();
	}
	
	bPrFreedomAttacking = false;
	bPreReleaseSkill = false;
	// 如果是发送移动或者攻击指令则在目标点生成粒子	
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, EndLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void ASame_DOTA_PlayerController::OnMouseRightClikInputStarted()
{
	MouseHitActor = nullptr;//重置鼠标命中的目标	
	
	GetMouseHitResultByChannal();
	EndLocation = MouseHitLocation;
	
}

void ASame_DOTA_PlayerController::OnMouseRightClikTriggered()
{

}

void ASame_DOTA_PlayerController::OnMouseRightClikReleased()
{
	//重置攻击或释放技能指令
	bPrFreedomAttacking = false;
	bPreReleaseSkill = false;

	//强制移动到点击位置
	if (!Selected_UnitsSelf.IsEmpty())
	{
		bool bHitActor = false;
		for (TObjectPtr<AActor> UnitPtr : Selected_UnitsSelf)
		{
			if (UnitPtr)
			{				
				if (MouseHitActor != nullptr)
				{
					if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(MouseHitActor))
					{
						MyCameraPawn_Ref->UnitBaseMoveToLocation(UnitPtr, EndLocation, NewChar);
						bHitActor = true;
					}
					else
					{
						
						MyCameraPawn_Ref->UnitBaseMoveToLocation(UnitPtr, EndLocation, nullptr);
					}
				}			
				else
				{
					// We move there and spawn some particles	
					
					
					MyCameraPawn_Ref->UnitBaseMoveToLocation(UnitPtr, EndLocation, nullptr);
				}				
			}
		}

		if (bHitActor != true)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor_Default, EndLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
		
	}
}

void ASame_DOTA_PlayerController::OnReleaseSkill_1Started()
{
	if (!Selected_UnitsSelf.IsEmpty())
	{
		MyCameraPawn_Ref->UnitReleaseSkill(Selected_UnitsSelf[0], 0);
	}
}

void ASame_DOTA_PlayerController::OnReleaseSkill_2Started()
{
	if (!Selected_UnitsSelf.IsEmpty())
	{
		MyCameraPawn_Ref->UnitReleaseSkill(Selected_UnitsSelf[0], 1);
	}
}

void ASame_DOTA_PlayerController::OnReleaseSkill_3Started()
{
	if (!Selected_UnitsSelf.IsEmpty())
	{
		MyCameraPawn_Ref->UnitReleaseSkill(Selected_UnitsSelf[0], 2);
	}
}

void ASame_DOTA_PlayerController::OnReleaseSkill_4Started()
{
	if (!Selected_UnitsSelf.IsEmpty())
	{
		MyCameraPawn_Ref->UnitReleaseSkill(Selected_UnitsSelf[0], 3);
	}
}

void ASame_DOTA_PlayerController::OnUnitFreedomAttackMoveStarted()
{
	if (!Selected_UnitsSelf.IsEmpty())
	{
		bPrFreedomAttacking = true;
	}
}

void ASame_DOTA_PlayerController::OnUnitPatrolStarted()
{
	if (!Selected_UnitsSelf.IsEmpty())
	{
		bPrePatrol = true;
		PatrolPoints.Empty();
	}	
}

void ASame_DOTA_PlayerController::OnUnitPatrolReleased()
{	
	if (!Selected_UnitsSelf.IsEmpty() && !PatrolPoints.IsEmpty())
	{
		bPrePatrol = false;

		//const TArray<FVector>& TempArray = PatrolPoints;

		for (AActor* NewUnit : Selected_UnitsSelf)
		{
			MyCameraPawn_Ref->UnitPatrol(NewUnit, PatrolPoints);
		}

		
	}	
}

