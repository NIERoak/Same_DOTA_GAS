// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Same_DOTA_AbilitySystemComponent.h"
#include "GAS/Same_DOTA_AttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"



void USame_DOTA_AbilitySystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USame_DOTA_AbilitySystemComponent, Skills_Level, COND_None, REPNOTIFY_Always);
}

void USame_DOTA_AbilitySystemComponent::ASC_InitCharAbilities()
{	
	if (AttackAbility_Class != nullptr)
	{
		//获取普攻能力
		GiveAbility(FGameplayAbilitySpec(AttackAbility_Class.GetDefaultObject(), 1));
	}

	//初始化技能
	if (!CharSkills_Class.IsEmpty())
	{
		for (TSubclassOf<UGameplayAbility> AbilityClass : CharSkills_Class)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 0);

			GiveAbility(AbilitySpec);

			Skills_Level.Add(0);

			if (USame_DOTA_GameplayAbilityBase* SkillInstance = Cast<USame_DOTA_GameplayAbilityBase>(AbilityClass.GetDefaultObject()))
			{
				SkillInstance->SetSkillIndex(Skills_Level.Num() - 1);
			}
		}
	}
	//对于被Ai控制器控制的Actor的初始化都放到Beginplay执行
	InitAbilityActorInfo(GetOwnerActor(), GetOwnerActor());	

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&USame_DOTA_AbilitySystemComponent::GameplayEffectApplied);
}

//GE应用成功的回调函数
void USame_DOTA_AbilitySystemComponent::GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		//Broadcast the tag to the widget controller

	}
}

void USame_DOTA_AbilitySystemComponent::ReceiveGamaplayEffectDamage(ASame_DOTA_CharacterBase* DamageSourceActor, EAblityType_DamageType AblityType_DamageType, float Damage)
{
	TSubclassOf<UGameplayEffect> GE_Class = nullptr;
	
	switch (AblityType_DamageType)
	{
	case EAblityType_DamageType::None:
		GE_Class = GE_PhysicalDamage_Class;
		break;
	case EAblityType_DamageType::PhysicalDamage:
		GE_Class = GE_MagicDamage_Class;
		break;
	case EAblityType_DamageType::MagicDamage:
		GE_Class = GE_RealDamage_Class;
		break;
	case EAblityType_DamageType::RealDamage:
		break;
	}
	
	BP_ApplyGameplayEffectToSelf(GE_Class, Damage, MakeEffectContext());
	
}




