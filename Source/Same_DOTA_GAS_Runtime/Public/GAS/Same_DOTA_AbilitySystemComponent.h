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
	//���縴�ƹ��ܱ���ʵ�ֵĺ���
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	//�����ɫ����
	void ASC_InitCharAbilities();

protected:
	void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,const FGameplayEffectSpec& EffectSpec,FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

public:

	//��ɫ���ܵȼ�
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ASC|Skills Level")
	TArray<int> Skills_Level;
	

public:
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|AbilitySystem Abilities")
	TSubclassOf<USame_DOTA_GameplayAbilityBase> AttackAbility_Class;//��ɫ����ͨ����	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ASC|AbilitySystem Abilities")
	TArray<TSubclassOf<USame_DOTA_GameplayAbilityBase>> CharSkills_Class;//��ɫ�ļ���

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|AbilitySystem Abilities")
	UAnimMontage* CharacterMontage;//��ɫ�Ķ�����̫��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|AbilitySystem Abilities")
	TArray<FString> MeleeMontageFragments;//��ɫ�չ��Ķ�����̫��Ƭ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASC|AbilitySystem Abilities")
	TArray<FString> ReleaseSkillMontageFragments;//��ɫ�ͷż��ܵĶ�����̫��Ƭ��

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
