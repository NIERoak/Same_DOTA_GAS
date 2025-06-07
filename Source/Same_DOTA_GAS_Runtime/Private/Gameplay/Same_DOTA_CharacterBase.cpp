// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "Net/UnrealNetwork.h"

#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"



#include "Gameplay/Same_DOTA_PlayerController.h"
#include "Gameplay/UI/Widget/Same_DOTA_WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"


#define ECC_PluginCustomObject ECC_Selected_Unit

//ע����Ҫ���縴�Ƶı���
void ASame_DOTA_CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ASame_DOTA_CharacterBase, bDeath, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(ASame_DOTA_CharacterBase, Char_TeamID, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ASame_DOTA_CharacterBase, Char_PlayerID, COND_None, REPNOTIFY_Always);	
	
}

// Sets default values
ASame_DOTA_CharacterBase::ASame_DOTA_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//����ASC
	AbilitySystemComponent = CreateDefaultSubobject<USame_DOTA_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);
		
	//����AS
	AttributeSet = CreateDefaultSubobject<USame_DOTA_AttributeSet>("AttributeSet");

	//�����������
	Decal_SelectedRing = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	Decal_SelectedRing->SetupAttachment(RootComponent);
	Decal_SelectedRing->SetVisibility(false);//Ĭ�ϲ�����
	Decal_SelectedRing->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(90.f, 0.f, 0.f));
	Decal_SelectedRing->DecalSize = FVector(30.f, 50.f, 50.f); 


	//�����û��ؼ����
	WidgetComponent = CreateDefaultSubobject<USame_DOTA_WidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASame_DOTA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	

	InitCharAbilities();

	SetSelectedRingMaterial();//����������ɫ

	WidgetComponent->SetOwnerCharacterRef(this);//����Widget�����ӵ��char

	if (!HasAuthority()) { return; };
	if (AAIController* NewCharPC = Cast<AAIController>(GetController()))
	{
		CharAiPC_Ref = NewCharPC;
		CharAiPC_Ref->ReceiveMoveCompleted.AddDynamic(this, &ASame_DOTA_CharacterBase::HandleCharMoveCompleted);//���ƶ����ɹ�ί��		
	}

}

// Called every frame
void ASame_DOTA_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void ASame_DOTA_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

USame_DOTA_AbilitySystemComponent* ASame_DOTA_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASame_DOTA_CharacterBase::InitCharAbilities()
{
	if (!HasAuthority()) { return; }

	if (AbilitySystemComponent != nullptr)
	{		
		AbilitySystemComponent->ASC_InitCharAbilities();		
	}
}

//���Բ�����ͨ�����Ķ�����̫��
void ASame_DOTA_CharacterBase::TryAttackAbility()
{	
	if (!bPlayingAnimationMontage)
	{
		if (AttackTargetChar)
		{
			bPlayingAnimationMontage = true;//���벥����ͨ�����Ķ�����̫��״̬
			StopAnimMontage();

			FRotator LookAtTargetRotator;
			FRotator SlefToTagerRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), AttackTargetChar->GetActorLocation());
			LookAtTargetRotator = FRotator(0.f, SlefToTagerRotator.Yaw, 0.f);
			SetActorRotation(LookAtTargetRotator);

			AbilitySystemComponent->TryActivateAbilityByClass(AbilitySystemComponent->AttackAbility_Class);				
		}
	}	
}

void ASame_DOTA_CharacterBase::ApplyMinAttackInterval()
{
	float Char_AttackSpeed = 100.0f;

	AttributeSet->GetAttackSpeed();

	float TimeLoop = 100 / Char_AttackSpeed;//ͨ�����ټ���ѭ������
	
	GetWorld()->GetTimerManager().SetTimer(
		ApplyMinAttackIntervalHandle,
		this,
		&ASame_DOTA_CharacterBase::TryMeleeLoop,
		TimeLoop,  // ���ʱ��
		true,  // ѭ��ִ��
		TimeLoop   // �״��ӳ�
	);
	
}

//����Ƿ�ѭ������
void ASame_DOTA_CharacterBase::TryMeleeLoop()
{	

	if (bDeath) { return; };

	if (!bPlayingAnimationMontage)//���ڲ��Ŷ�����̫���в����ƶ�
	{
		if (AttackTargetChar != nullptr)
		{
			if (!bDeath && !AttackTargetChar->bDeath)
			{
				AttackMoveToActor(AttackTargetChar);//�����ƶ���ָ���з�Ŀ��󹥻�
			}
			else
			{
				AttackTargetChar = nullptr;
			}
		}
	}	
}

//�����ƶ���ָ���з�Ŀ��󹥻�
void ASame_DOTA_CharacterBase::AttackMoveToActor(ASame_DOTA_CharacterBase* TargetActor)
{
	if (bDeath || TargetActor->bDeath) { return; };
	
	bAttackToActor = true;//����ǿ�ƹ���ĳ��Ŀ��״̬
	
	float AttackRang = -1.0f;
	
	AttackRang = AttributeSet->GetAttackRange();	
	
	CharAiPC_Ref->MoveToActor(TargetActor, AttackRang);
}

//���ɹ���
void ASame_DOTA_CharacterBase::FreedomAttack()
{
	if (bDeath) { return; };
	
	if (!bFindNearestActor)
	{
		const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(Unit) };
		TArray<AActor*> IgnoreActors;
		TArray<FHitResult> OutHits;

		bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
			GetWorld(), GetActorLocation(), GetActorLocation(), 800.0f, ObjectTypes,
			false, IgnoreActors, EDrawDebugTrace::None, OutHits, true, FColor::Green, FColor::Red, 0.0f);

		if (bHit)
		{
			WithinRangeEnemies.Empty();

			ASame_DOTA_CharacterBase* NearestActor = nullptr;
			float MinDistance = FLT_MAX;//��ʼ��Ϊ������ֵ

			for (const FHitResult& Hit : OutHits)
			{
				AActor* HitActor = Hit.GetActor();
				if (HitActor)
				{
					if (ASame_DOTA_CharacterBase* HitChar = Cast<ASame_DOTA_CharacterBase>(HitActor))
					{
						if (!HitChar->bDeath)
						{
							if (HitChar->Char_TeamID != Char_TeamID)
							{
								float Distance = FVector::Dist(GetActorLocation(), HitChar->GetActorLocation());
								if (Distance < MinDistance)
								{
									MinDistance = Distance;
									NearestActor = HitChar;
								}
							}
						}

					}
				}
			}
			if (NearestActor)
			{
				AttackTargetChar = NearestActor;
				bFindNearestActor = true;
			}
		}
		else
		{
			AttackTargetChar = nullptr;			
		}
	}
	else if(!bMovingToNearestActor)
	{
		if (AttackTargetChar)
		{
			bMovingToNearestActor = true;//����������ƶ�
			
			AttackMoveToActor(AttackTargetChar);						
		}		
	}
	
	
}

//�ƶ�����һ��Ѳ�ߵ�
void ASame_DOTA_CharacterBase::PatrolMoveToPoint(int Index)
{		
	if (!HasAuthority()) { return; }
	if (!PartolLocationPoints.IsEmpty())
	{
		FVector TargetLocation = PartolLocationPoints[Index];
		
		CharAiPC_Ref->MoveToLocation(TargetLocation, 50.f);
	}
}

//ʵ���Զ���ӿں���
void ASame_DOTA_CharacterBase::UnitMoveTo_Implementation(FVector InLocation, AActor* HitActor)
{		
	ReSetCharAllState();
	
	if (bDeath) { return; };

	if (HitActor != nullptr)
	{
		if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(HitActor))
		{
			if (NewChar->Char_TeamID== Char_TeamID)
			{
				AttackTargetChar = nullptr;
				
				
				float MoveRang = -1.0f;
				
				MoveRang = AttributeSet->GetAttackRange();
				
				CharAiPC_Ref->MoveToActor(NewChar, MoveRang);

			}
			else
			{
				AttackTargetChar = NewChar;
				
				AttackMoveToActor(AttackTargetChar);				
			}
		}
	}
	else
	{
		AttackTargetChar = nullptr;
		
	
		float MoveRang = -1.0f;
		CharAiPC_Ref->MoveToLocation(InLocation, MoveRang);
	}	
	
}

void ASame_DOTA_CharacterBase::UnitAttackMoveTo_Implementation(FVector InLocation, bool bFreedomAttack)
{
	ReSetCharAllState();
	
	if (bDeath) { return; };

	bFreedomAttacking = bFreedomAttack;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), InLocation);
}

void ASame_DOTA_CharacterBase::UnitPatrol_Implementation(const TArray<FVector>& InLocationPoints)
{
	ReSetCharAllState();
	
	if (bDeath) { return; };

	bPrePatrol = true;	

	for (FVector Point : InLocationPoints)
	{
		FVector Location = Point;
		
		PartolLocationPoints.Add(Location);
	}	

	PatrolMoveToPoint(LastIndex);//Ѳ���ƶ�����һ����
}

void ASame_DOTA_CharacterBase::TryReleaseSkill_Implementation(int InSkillIndex)
{
	ReSetCharAllState();

	CharReleaseSkill(InSkillIndex);
}

FVector ASame_DOTA_CharacterBase::GetSocketLocation_Implementation(FName InSocketName)
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	if (!SkeletalMesh) return FVector();

	FTransform SocketTransform = SkeletalMesh->GetSocketTransform(InSocketName);
	
	FVector SocketLocation = SocketTransform.GetLocation();

	return SocketLocation;
}

void ASame_DOTA_CharacterBase::HandleCharMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	
	switch (Result)
	{
	case EPathFollowingResult::Success:
		if (bAttackToActor)//����Ҫ���ڹ���ָ��Ŀ���״̬
		{				
			if (!bApplyingMeleeLoop)
			{
				bApplyingMeleeLoop = true;//����ѭ���������״̬
				ApplyMinAttackInterval();//���û����ѭ���������������ѭ���������
			}
			TryAttackAbility();
		}
		else if (bPrePatrol)
		{
			if (PartolLocationPoints.Num() > LastIndex + 1)
			{
				++LastIndex;
				PatrolMoveToPoint(LastIndex);				
			}
			else
			{
				LastIndex = 0;
				PatrolMoveToPoint(LastIndex);
			}
		}
		else
		{

		}
		break;
	case EPathFollowingResult::Blocked:
		
		break;
	case EPathFollowingResult::OffPath:
		
		break;
	}
	
}





//�ڷ����������ý�ɫ�Ķ�������ID
void ASame_DOTA_CharacterBase::Server_SetCharTeamIDandPlayerID_Implementation(ETeamID InTeamID, EPlayerID InPlayerID)
{
	Char_TeamID = InTeamID;
	Char_PlayerID = InPlayerID;
}
bool ASame_DOTA_CharacterBase::Server_SetCharTeamIDandPlayerID_Validate(ETeamID InTeamID, EPlayerID InPlayerID)
{
	return true;
}

//���ý�ɫ����״̬
void ASame_DOTA_CharacterBase::ReSetCharAllState()
{
	if (ApplyMinAttackIntervalHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ApplyMinAttackIntervalHandle);//ȡ����ͨѭ��
	}	

	if (AbilitySystemComponent->CharacterMontage)
	{
		StopAnimMontage(AbilitySystemComponent->CharacterMontage);//ֹͣ��ǰ���ŵĶ�����̫��
	}			

	bPlayingAnimationMontage = false;//�Ƿ��ڲ��Ŷ�����
	bApplyingMeleeLoop = false;//�Ƿ���ѭ����ͨ������
	bAttackToActor = false;//ǿ�ƹ���ĳ��Ŀ��
	bFreedomAttacking = false;//�Ƿ������ɹ���ģʽ
	bFindNearestActor = false;//�Ƿ��ҵ�����ĵ���	
	bMovingToNearestActor = false;	//�Ƿ������ƶ������
	bPrePatrol = false;//�Ƿ�����Ѳ��
	LastIndex = 0;//����Ѳ�ߵ�Index

	PartolLocationPoints.Empty();
}



void ASame_DOTA_CharacterBase::Server_UpSkillsLevel_Implementation(int InSkillIndex, int InAddLevels)
{
	if (!AbilitySystemComponent->Skills_Level.IsEmpty())
	{
		AbilitySystemComponent->Skills_Level[InSkillIndex] += InAddLevels;
	}		
}

bool ASame_DOTA_CharacterBase::Server_UpSkillsLevel_Validate(int InSkillIndex, int InAddLevels)
{
	return true;
}



FGamepalyAbilityInfo ASame_DOTA_CharacterBase::GetAbilityInfoByClass(TSubclassOf<USame_DOTA_GameplayAbilityBase> Ability_Class, int InLevel)
{	
	USame_DOTA_GameplayAbilityBase* AbilityInstance = Ability_Class->GetDefaultObject<USame_DOTA_GameplayAbilityBase>();
	if (AbilitySystemComponent && AbilityInstance)
	{
		return AbilityInstance->GetAbilityInfo(InLevel);
	}	
	return FGamepalyAbilityInfo();
}

//�ͷ���������
void ASame_DOTA_CharacterBase::CharReleaseSkill(int Skill_Index)
{
	if (bDeath) { return; };

	ReSetCharAllState();

	if (!AbilitySystemComponent->CharSkills_Class.IsEmpty())
	{
		if (AbilitySystemComponent->CharSkills_Class.Num() > Skill_Index)
		{
			FGamepalyAbilityInfo NewAbilityInfo = GetAbilityInfoByClass(AbilitySystemComponent->CharSkills_Class[Skill_Index], AbilitySystemComponent->Skills_Level[Skill_Index]);

			if (NewAbilityInfo.AblityType_Type == EAblityType_Type::Actived)
			{
				AbilitySystemComponent->TryActivateAbilityByClass(AbilitySystemComponent->CharSkills_Class[Skill_Index]);
			}
		}
	}	
}

void ASame_DOTA_CharacterBase::SetSelectedRingMaterial()
{
	
	if (Decal_SelectedRing)
	{		
		
		DynMaterialInstance = Decal_SelectedRing->CreateDynamicMaterialInstance();
		
		APlayerController* LocalPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (ASame_DOTA_PlayerController* NewPC = Cast<ASame_DOTA_PlayerController>(LocalPC))
		{
			if (NewPC->PC_TeamID == Char_TeamID)
			{
				if (NewPC->PC_PlayerID == Char_PlayerID)
				{					
					DynMaterialInstance->SetVectorParameterValue(TEXT("Color"), SelfUnit_Color);
				}
				else
				{					
					DynMaterialInstance->SetVectorParameterValue(TEXT("Color"), FriendUnit_Color);
				}
			}
			else 
			{				
				DynMaterialInstance->SetVectorParameterValue(TEXT("Color"), EnemyUnit_Color);
			}			
		}				
	}
}

void ASame_DOTA_CharacterBase::SetSelectedRingVisibility(bool bVisible)
{
	if (Decal_SelectedRing)
	{
		Decal_SelectedRing->SetVisibility(bVisible);		
	}
}

