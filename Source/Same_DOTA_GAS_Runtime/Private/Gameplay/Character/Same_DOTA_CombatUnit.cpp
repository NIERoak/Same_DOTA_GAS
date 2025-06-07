// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Character/Same_DOTA_CombatUnit.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GAS/Same_DOTA_AttributeSet.h"

void ASame_DOTA_CombatUnit::BeginPlay()
{
	Super::BeginPlay();


	ApplyUnitHealthRecover();

	
}

void ASame_DOTA_CombatUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFreedomAttacking)
	{
		FreedomAttack();//��ս��λ�Ž��ез�Ŀ����
	}
}

//�Ѿ�����
void ASame_DOTA_CombatUnit::SetTimerToRecoverLoop()
{
	GetWorld()->GetTimerManager().SetTimer(
		HealthRecoverTimerHandle,
		this,
		&ASame_DOTA_CombatUnit::ApplyUnitHealthRecover,
		1.0f,  // ���ʱ��
		true,  // ѭ��ִ��
		1.0f   // �״��ӳ�
	);
}

void ASame_DOTA_CombatUnit::ApplyUnitHealthRecover()
{	
	if (!HasAuthority()) return;
	
	if (!bDeath)
	{
		if (AbilitySystemComponent)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();			

			//EffectContext.AddInstigator(GetController(), this);
			//EffectContext.AddSourceObject(this);			

			const USame_DOTA_AttributeSet* NewAS = CastChecked<USame_DOTA_AttributeSet>(AttributeSet);
			float CurrentHealthRecoverRate = NewAS->GetHealthRecoveryRate();
			float CurrentManaRecoverRate = NewAS->GetManaRecoveryRate();

			AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(GE_HealthRecover_Class, CurrentHealthRecoverRate, EffectContext);
			AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(GE_ManaRecover_Class, CurrentManaRecoverRate, EffectContext);

		}
	}
	
}
