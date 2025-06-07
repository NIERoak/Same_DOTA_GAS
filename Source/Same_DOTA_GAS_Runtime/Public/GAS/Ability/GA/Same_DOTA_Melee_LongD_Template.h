// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/Actor/Same_DOTA_MeleeProjectile.h"

#include "Same_DOTA_Melee_LongD_Template.generated.h"


/**
 * 
 */
UCLASS()
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_Melee_LongD_Template : public USame_DOTA_GameplayAbilityBase
{
	GENERATED_BODY()

public:
	USame_DOTA_Melee_LongD_Template();
	
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
	void OnShootEvent(const FGameplayEventData Payload);

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Melee")
	TSubclassOf<ASame_DOTA_MeleeProjectile> Projectile_Class;		

	UFUNCTION(BlueprintCallable, Category = "Melee")
	void SpawnProjectileActor();
};
