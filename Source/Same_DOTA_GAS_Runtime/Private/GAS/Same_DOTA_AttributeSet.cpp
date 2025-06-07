// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Same_DOTA_AttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


USame_DOTA_AttributeSet::USame_DOTA_AttributeSet()
{
	InitCharLevel(1.f);
	InitExperience(0.f);
	InitMaxExperience(500.f);
	InitHealth(1000.f);
	InitMaxHealth(1000.f);
	InitHealthRecoveryRate(1.f);
	InitMana(500.f);
	InitMaxMana(500.f);
	InitManaRecoveryRate(1.f);
	InitAttack(50.f);
	InitAttackSpeed(50.f);
	InitMinAttackInterval(0.75f);
	InitAttackRange(100.f);
	InitEnhancedCastingDistance(0.f);
	InitDefense(3.f); 
	InitMagicResistance(0.f);
	InitMoveSpeed(300.f);
}

void USame_DOTA_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, CharLevel, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, Experience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, MaxExperience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, Health, COND_None, REPNOTIFY_Always);//注册网络复制属性的健康状态
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, HealthRecoveryRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, ManaRecoveryRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, MinAttackInterval, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, AttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, EnhancedCastingDistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}
//属性改变前调用

void USame_DOTA_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		if (NewValue <= GetHealth())
		{
			SetHealth(FMath::Clamp(GetHealth(), 0.0f, NewValue));
		}
	}
	if (Attribute == GetMaxManaAttribute())
	{
		if (NewValue <= GetMana())
		{
			SetMana(FMath::Clamp(GetMana(), 0.0f, NewValue));
		}
	}

}
//属性改变后调用
void USame_DOTA_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.0f,GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	
}

void USame_DOTA_AttributeSet::OnRep_CharLevel(const FGameplayAttributeData& OldCharLevel) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, CharLevel, OldCharLevel);
}

void USame_DOTA_AttributeSet::OnRep_Experience(const FGameplayAttributeData& OldExperience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, Experience, OldExperience);
}

void USame_DOTA_AttributeSet::OnRep_MaxExperience(const FGameplayAttributeData& OldMaxExperience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, MaxExperience, OldMaxExperience);
}

void USame_DOTA_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	//控制属性的OnRep行为
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, Health, OldHealth);
}

void USame_DOTA_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, MaxHealth, OldMaxHealth);
}

void USame_DOTA_AttributeSet::OnRep_HealthRecoveryRate(const FGameplayAttributeData& OldHealthRecoveryRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, HealthRecoveryRate, OldHealthRecoveryRate);
}

void USame_DOTA_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, Mana, OldMana);
}

void USame_DOTA_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, MaxMana, OldMaxMana);
}

void USame_DOTA_AttributeSet::OnRep_ManaRecoveryRate(const FGameplayAttributeData& OldManaRecoveryRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, ManaRecoveryRate, OldManaRecoveryRate);
}

void USame_DOTA_AttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, Attack, OldAttack);
}

void USame_DOTA_AttributeSet::OnRep_MinAttackInterval(const FGameplayAttributeData& OldMinAttackInterval) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, MinAttackInterval, OldMinAttackInterval);
}

void USame_DOTA_AttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, AttackSpeed, OldAttackSpeed);
}

void USame_DOTA_AttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, AttackRange, OldAttackRange);
}

void USame_DOTA_AttributeSet::OnRep_EnhancedCastingDistance(const FGameplayAttributeData& OldEnhancedCastingDistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, EnhancedCastingDistance, OldEnhancedCastingDistance);
}

void USame_DOTA_AttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, Defense, OldDefense);
}

void USame_DOTA_AttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, MagicResistance, OldMagicResistance);
}

void USame_DOTA_AttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USame_DOTA_AttributeSet, MoveSpeed, OldMoveSpeed);
}


