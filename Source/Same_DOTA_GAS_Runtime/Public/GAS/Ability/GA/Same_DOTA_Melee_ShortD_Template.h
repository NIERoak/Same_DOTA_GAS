// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"
#include "GAS/Actor/Same_DOTA_MeleeDamageSphere.h"

#include "Same_DOTA_Melee_ShortD_Template.generated.h"

/**
 * 
 */
UCLASS()
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_Melee_ShortD_Template : public USame_DOTA_GameplayAbilityBase
{
	GENERATED_BODY()

public:
	USame_DOTA_Melee_ShortD_Template();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void InitAbilityInfo() override;

public:

	void PlayAnimationMontage();

	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled();
	UFUNCTION()
	void OnMontageBlendOut();
	UFUNCTION()
	void OnMontageInterrupted();

	UFUNCTION()
	void OnHitEvent(const FGameplayEventData Payload);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	TSubclassOf<ASame_DOTA_MeleeDamageSphere> DamageSphere_Class;

	UFUNCTION(BlueprintCallable, Category = "Melee")
	void SpawnDamageActor();
};
