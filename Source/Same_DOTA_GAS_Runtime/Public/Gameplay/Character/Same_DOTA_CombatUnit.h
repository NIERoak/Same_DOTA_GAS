// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "Same_DOTA_CombatUnit.generated.h"

/**
 * 
 */
UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_CombatUnit : public ASame_DOTA_CharacterBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//HP and MP recover/s
	void InitHealthRecover();

	FTimerHandle HealthRecoverTimerHandle;

	void SetTimerToRecoverLoop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatUnit|HealthRecover")
	TSubclassOf<UGameplayEffect> GE_HealthRecover_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CombatUnit|HealthRecover")
	TSubclassOf<UGameplayEffect> GE_ManaRecover_Class;

	UFUNCTION(BlueprintCallable, Category = "CombatUnit HealthRecover")
	void ApplyUnitHealthRecover();



};
