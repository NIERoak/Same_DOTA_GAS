// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Actor/Same_DOTA_ActorBase.h"
#include "Same_DOTA_MeleeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_MeleeProjectile : public ASame_DOTA_ActorBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASame_DOTA_MeleeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
