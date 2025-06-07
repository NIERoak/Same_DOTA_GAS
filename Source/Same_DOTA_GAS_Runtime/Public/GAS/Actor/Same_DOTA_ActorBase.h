// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"

#include "Same_DOTA_ActorBase.generated.h"

//自定义一个Unit的object检测通道
#define Unit ECC_GameTraceChannel1

class ASame_DOTA_CharacterBase;


UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_ActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASame_DOTA_ActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Info")
	TObjectPtr<ASame_DOTA_CharacterBase> OwnerActor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Info")
	TObjectPtr<ASame_DOTA_CharacterBase> TagetActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Info")
	EAblityType_DamageType AblityType_DamageType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Info")
	float Damage;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetOwnerActorTagetActorAndDamageType(ASame_DOTA_CharacterBase* InOwnerActor, ASame_DOTA_CharacterBase* InTagetActor, EAblityType_DamageType InAblityType_DamageType, float InDamage);
};
