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


//ע����Ҫ���縴�Ƶı���
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
		TraceTypeQuery1,  // ������ײͨ������ɼ��ԡ�������ȣ�
		false,                              // �Ƿ���Ը�����ײ��ͨ��Ϊ false��
		HitResult                           // ������н��
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
						OldSelectedActor->SetSelectedRingVisibility(false);//��ѡ��򲻿���
					}
				}
				if (ASame_DOTA_CharacterBase* OldSelectedActor = Cast<ASame_DOTA_CharacterBase>(Selected_UnitFriend))
				{
					OldSelectedActor->SetSelectedRingVisibility(false);//��ѡ��򲻿���
				}
				if (ASame_DOTA_CharacterBase* OldSelectedActor = Cast<ASame_DOTA_CharacterBase>(Selected_UnitEnemy))
				{
					OldSelectedActor->SetSelectedRingVisibility(false);//��ѡ��򲻿���
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
							SelectedActor->SetSelectedRingVisibility(true);//��ѡ������
							Selected_UnitsSelf.Add(SelectedActor);
							bSelectedSelfUnits = true;
							//ʵ�ֵ�λ����ѡ��ĺ���
							MyHUD_Ref->UpdateMainMenu();//����һ�����˵�
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
						SelectedActor->SetSelectedRingVisibility(true);//��ѡ������
						//ʵ�ֵ�λ����ѡ��ĺ���
						MyHUD_Ref->UpdateMainMenu();//����һ�����˵�
						
						
						break;
					    }
						else
						{
							if (!SelectedActor->bDeath) {

								Selected_UnitEnemy = SelectedActor;
								SelectedActor->SetSelectedRingVisibility(true);//��ѡ������							

							};

							MyHUD_Ref->UpdateMainMenu();//����һ�����˵�
							break;
						}
					 
					}
					
					
				}
			}
		}		
	}
}

//���ö�������ID
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
		//������������¼�
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnMouseLeftClikInputStarted);
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Triggered, this, &ASame_DOTA_PlayerController::OnMouseLeftClikTriggered);
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Completed, this, &ASame_DOTA_PlayerController::OnMouseLeftClikReleased);
		EnhancedInputComponent->BindAction(SetMouseLeftClickAction, ETriggerEvent::Canceled, this, &ASame_DOTA_PlayerController::OnMouseLeftClikReleased);
		//������Ҽ�����¼�
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnMouseRightClikInputStarted);
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Triggered, this, &ASame_DOTA_PlayerController::OnMouseRightClikTriggered);
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Completed, this, &ASame_DOTA_PlayerController::OnMouseRightClikReleased);
		EnhancedInputComponent->BindAction(SetMouseRightClickAction, ETriggerEvent::Canceled, this, &ASame_DOTA_PlayerController::OnMouseRightClikReleased);
		
		//�ͷż��ܰ���
		EnhancedInputComponent->BindAction(ReleaseSkill_1, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_1Started);
		EnhancedInputComponent->BindAction(ReleaseSkill_2, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_2Started);
		EnhancedInputComponent->BindAction(ReleaseSkill_3, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_3Started);
		EnhancedInputComponent->BindAction(ReleaseSkill_4, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnReleaseSkill_4Started);

		//���ɹ����ƶ�����
		EnhancedInputComponent->BindAction(UnitFreedomAttackMoveAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnUnitFreedomAttackMoveStarted);
		
		//Ѳ��
		EnhancedInputComponent->BindAction(UnitPatrolAction, ETriggerEvent::Started, this, &ASame_DOTA_PlayerController::OnUnitPatrolStarted);
		EnhancedInputComponent->BindAction(UnitPatrolAction, ETriggerEvent::Completed, this, &ASame_DOTA_PlayerController::OnUnitPatrolReleased);
	}
}

//��ʼ����һ��
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

						//�������ɹ����ƶ���λ��
						for (AActor* SeletedUnitSelf : Selected_UnitsSelf)
						{
							MyCameraPawn_Ref->UnitFreedomAttackMoveToLocation(SeletedUnitSelf, StartLocation, true);
						}
						
					}
				}
				else
				{					
					//�������ɹ����ƶ���λ��
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
		//�����ͷ��߼�
	}
	else
	{
		//�洢����һ�ε����λ��
		bOnMouseDrag = true;//��갴��
		
	}	
}

//�����ڼ��������
void ASame_DOTA_PlayerController::OnMouseLeftClikTriggered()
{
	if (!bPrFreedomAttacking && !bPrePatrol && !bPreReleaseSkill)
	{
		//����Ļ�滭����
		if (MyHUD_Ref)
		{
			MyHUD_Ref->StartDrawBoxOnScreen(bOnMouseDrag, StartLocation);
		}
	}
}
	
//��������
void ASame_DOTA_PlayerController::OnMouseLeftClikReleased()
{
	if (!bPrFreedomAttacking)
	{
		bOnMouseDrag = false;//����ɿ�

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
	// ����Ƿ����ƶ����߹���ָ������Ŀ�����������	
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, EndLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void ASame_DOTA_PlayerController::OnMouseRightClikInputStarted()
{
	MouseHitActor = nullptr;//����������е�Ŀ��	
	
	GetMouseHitResultByChannal();
	EndLocation = MouseHitLocation;
	
}

void ASame_DOTA_PlayerController::OnMouseRightClikTriggered()
{

}

void ASame_DOTA_PlayerController::OnMouseRightClikReleased()
{
	//���ù������ͷż���ָ��
	bPrFreedomAttacking = false;
	bPreReleaseSkill = false;

	//ǿ���ƶ������λ��
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

