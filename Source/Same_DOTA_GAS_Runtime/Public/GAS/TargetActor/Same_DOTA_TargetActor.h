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
	//���ظ��ຯ��

	virtual void StartTargeting(UGameplayAbility* Ability) override;//����BeginPlay

	virtual void ConfirmTargetingAndContinue() override;//����һ���㲥Data���ݳ�ȥ��һ��Handle

	//�Զ��庯��
	UFUNCTION()
	bool GetMouseLocation(FVector& InMousePoint);



	//�Զ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Target Actor")
	float SelectedRadius;


};
