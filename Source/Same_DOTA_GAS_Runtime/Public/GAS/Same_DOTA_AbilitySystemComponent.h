// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"
#include "Ability/GE/Same_DOTA_GE_PhysicalDamage.h"
#include "Ability/GE/Same_DOTA_GE_MagicDamage.h"
#include "Ability/GE/Same_DOTA_GE_RealDamage.h"

#include "Same_DOTA_AbilitySystemComponent.generated.h"



class USame_DOTA_GameplayAbilityBase;
class ASame_DOTA_CharacterBase;


UCLASS(BlueprintType)
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	

public:
	//网络复制功能必须实现的函数
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//给予角色技能
	void ASC_InitCharAbilities();

protected:
	void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

public:

	//角色技能等级
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ASC|Skills Level")
	TArray<int> Skills_Level;
	

public:
	//技能
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|AbilitySystem Abilities")
	TSubclassOf<USame_DOTA_GameplayAbilityBase> AttackAbility_Class;//角色的普通攻击	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|AbilitySystem Abilities")
	TArray<TSubclassOf<USame_DOTA_GameplayAbilityBase>> CharSkills_Class;//角色的技能

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|AbilitySystem Abilities")
	UAnimMontage* CharacterMontage;//角色的动画蒙太奇

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|AbilitySystem Abilities")
	TArray<FString> MeleeMontageFragments;//角色普攻的动画蒙太奇片段

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|AbilitySystem Abilities")
	TArray<FString> ReleaseSkillMontageFragments;//角色释放技能的动画蒙太奇片段

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|ReceiveDamage")
	TSubclassOf<USame_DOTA_GE_PhysicalDamage> GE_PhysicalDamage_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|ReceiveDamage")
	TSubclassOf<USame_DOTA_GE_MagicDamage> GE_MagicDamage_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|ReceiveDamage")
	TSubclassOf<USame_DOTA_GE_RealDamage> GE_RealDamage_Class;
	
	UFUNCTION(BlueprintCallable, Category = "ASC|ReceiveDamage")
	void ReceiveGamaplayEffectDamage(ASame_DOTA_CharacterBase* DamageSourceActor, EAblityType_DamageType AblityType_DamageType, float Damage);

};
