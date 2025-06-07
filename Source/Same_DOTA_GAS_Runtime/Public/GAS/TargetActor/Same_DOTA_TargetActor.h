// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Abilities/GameplayAbility.h"



#include "Same_DOTA_TargetActor.generated.h"

/**
 * 
 */
UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_TargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	//重载父类函数

	virtual void StartTargeting(UGameplayAbility* Ability) override;//类似BeginPlay

	virtual void ConfirmTargetingAndContinue() override;//返回一个广播Data数据出去的一个Handle

	//自定义函数
	UFUNCTION()
	bool GetMouseLocation(FVector& InMousePoint);



	//自定义变量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Target Actor")
	float SelectedRadius;


};
