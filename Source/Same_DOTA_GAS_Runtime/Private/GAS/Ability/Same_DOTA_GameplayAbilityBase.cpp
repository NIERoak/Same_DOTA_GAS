// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"

#include "GAS/Same_DOTA_AbilitySystemComponent.h"

FGamepalyAbilityInfo::FGamepalyAbilityInfo():
	AblityType_LoadType(EAblityType_LoadType::None),
	AblityType_Type(EAblityType_Type::None),
	AblityType_ActivelyTrigger(EAblityType_ActivelyTrigger::None),
	AblityType_PassivelyTrigger(EAblityType_PassivelyTrigger::None),
	AblityType_EffectedType(EAblityType_EffectedType::None),
	AblityType_EffectedUnit(EAblityType_EffectedUnit::None),
	CoolDownEffect_Tags(),
	CoolDown(0), 
	AblityType_Cost(EAblityType_Cost::MP),
	AblityType_DamageType(EAblityType_DamageType::None),
	CostValue(0),
	AbilityIcon(nullptr),
	Ability_Class(nullptr)
{

}

FGamepalyAbilityInfo::FGamepalyAbilityInfo(
	EAblityType_LoadType InAblityType_LoadType,
	EAblityType_Type InAblityType_Type,
	EAblityType_ActivelyTrigger InAblityType_ActivelyTrigger,
	EAblityType_PassivelyTrigger InAblityType_PassivelyTrigger,
	EAblityType_EffectedType InAblityType_EffectedType,
	EAblityType_EffectedUnit InAblityType_EffectedUnit,
	FGameplayTagContainer InCoolDownEffect_Tags,
	float InCoolDown,
	EAblityType_Cost InAblityType_Cost,
	EAblityType_DamageType InAblityType_DamageType,
	float InCostValue,
	UTexture2D* InAbilityIcon,
	TSubclassOf<USame_DOTA_GameplayAbilityBase> InAbility_Class) :

	AblityType_LoadType(InAblityType_LoadType),
	AblityType_Type(InAblityType_Type),
	AblityType_ActivelyTrigger(InAblityType_ActivelyTrigger),
	AblityType_PassivelyTrigger(InAblityType_PassivelyTrigger),
	AblityType_EffectedType(InAblityType_EffectedType),
	AblityType_EffectedUnit(AblityType_EffectedUnit),
	CoolDownEffect_Tags(InCoolDownEffect_Tags),
	CoolDown(InCoolDown),
	AblityType_Cost(AblityType_Cost),
	AblityType_DamageType(InAblityType_DamageType),
	CostValue(InCostValue),
	AbilityIcon(InAbilityIcon),
	Ability_Class(InAbility_Class)
{

}








//TryAbility
void USame_DOTA_GameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{	
	
}

//API
void USame_DOTA_GameplayAbilityBase::InitAbilityInfo()
{
	OwnerActor = Cast<ASame_DOTA_CharacterBase>(GetOwningActorFromActorInfo());
	TargetActor = OwnerActor->AttackTargetChar;
}

void USame_DOTA_GameplayAbilityBase::SetSkillIndex(int InIndex)
{
	SkillIndex = InIndex;
}

void USame_DOTA_GameplayAbilityBase::SetItemAbilityIndex(int InIndex)
{
	ItemAbilityIndex = InIndex;
}

FGamepalyAbilityInfo USame_DOTA_GameplayAbilityBase::GetAbilityInfo(int InLevel)
{
	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	float CD = 0;
	float CostValue = 0;
	EAblityType_Cost CostType = EAblityType_Cost::MP;
	
	FGameplayTagContainer CoolDownEffect_Tags;
	
	if (CoolDownEffect && CostEffect)
	{
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, CD);
		
		CoolDownEffect_Tags = CoolDownEffect->GetAssetTags();

		if (!CostEffect->Modifiers.IsEmpty())
		{
			FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
			CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, CostValue);
			FString CostTypeName = CostEffectModifierInfo.Attribute.AttributeName;

			if (CostTypeName == "Health")
			{
				CostType = EAblityType_Cost::HP;
			}
			if (CostTypeName == "Mana")
			{
				CostType = EAblityType_Cost::MP;
			}
			else
			{
				CostType = EAblityType_Cost::None;
			}
		}
		return FGamepalyAbilityInfo(AblityType_LoadType, AblityType_Type, AblityType_ActivelyTrigger, AblityType_PassivelyTrigger, AblityType_EffectedType, AblityType_EffectedUnit, CoolDownEffect_Tags, CD, CostType, AblityType_DamageType,CostValue, AbilityIcon, GetClass());
	}	
	else
	{
		CostType = EAblityType_Cost::None;
	}
	
	return FGamepalyAbilityInfo(AblityType_LoadType, AblityType_Type, AblityType_ActivelyTrigger, AblityType_PassivelyTrigger, AblityType_EffectedType, AblityType_EffectedUnit, CoolDownEffect_Tags, CD, CostType, AblityType_DamageType,CostValue, AbilityIcon, GetClass());
}

UAnimMontage* USame_DOTA_GameplayAbilityBase::GetCharAnimationMontage()
{
	if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(GetAvatarActorFromActorInfo())) 
	{
		return NewChar->GetAbilitySystemComponent()->CharacterMontage;
	}		
	return nullptr;
}

FString USame_DOTA_GameplayAbilityBase::GetCharMeleeAnimationMontageFragmentName()
{
	if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(GetAvatarActorFromActorInfo())) 
	{	
		int RandomIndex = FMath::RandRange(0, NewChar->GetAbilitySystemComponent()->MeleeMontageFragments.Num() - 1);

		return NewChar->GetAbilitySystemComponent()->MeleeMontageFragments[RandomIndex];		
	}
	return FString();
}

FString USame_DOTA_GameplayAbilityBase::GetCharReleaseSkillAnimationMontageFragmentName(int InSkillAnimationIndex)
{
	if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(GetAvatarActorFromActorInfo())) 
	{
		return NewChar->GetAbilitySystemComponent()->ReleaseSkillMontageFragments[InSkillAnimationIndex];		
	}
	return FString();
}

void USame_DOTA_GameplayAbilityBase::SetCharPlayingAnimationMontageCompleted()
{
	if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(GetAvatarActorFromActorInfo()))
	{
		NewChar->bPlayingAnimationMontage = false;//¶¯»­ÃÉÌ«Ææ²¥·Å½áÊø		
	}
}

