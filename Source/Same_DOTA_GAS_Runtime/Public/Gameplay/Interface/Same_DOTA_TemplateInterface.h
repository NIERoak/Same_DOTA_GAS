// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Same_DOTA_TemplateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class USame_DOTA_TemplateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SAME_DOTA_GAS_RUNTIME_API ISame_DOTA_TemplateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Move To")
	void UnitMoveTo(FVector InLocation, AActor* HitActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Attack Move")
	void UnitAttackMoveTo(FVector InLocation, bool bFreedomAttack);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit Patrol")
	void UnitPatrol(const TArray<FVector>& InLocationPoints);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit TryReleaseSkill")
	void TryReleaseSkill(int InSkillIndex);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface|Unit TryReleaseSkill")
	FVector GetSocketLocation(FName InSocketName);
};
