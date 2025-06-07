// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "Same_DOTA_CameraPawn.generated.h"

UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_CameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASame_DOTA_CameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
public:
	//基础强制移动函数
	UFUNCTION(BlueprintCallable, Category = "Unit Base Move")
	void UnitBaseMoveToLocation(AActor* TargetUnit,FVector InLocation, AActor* HitActor);

	UFUNCTION(Server, Unreliable, WithValidation, Category = "Unit Base Move")
	void Server_UnitBaseMoveToLocation(AActor* TargetUnit,FVector InLocation, AActor* HitActor);
	virtual bool Server_UnitBaseMoveToLocation_Validate(AActor* TargetUnit, FVector InLocation, AActor* HitActor);

	UFUNCTION(Client, Unreliable, Category = "Unit Base Move")
	void Client_UnitBaseMoveToLocation(AActor* TargetUnit,FVector InLocation, AActor* HitActor);

	//自由攻击移动函数

	UFUNCTION(BlueprintCallable, Category = "Unit Attack Move")
	void UnitFreedomAttackMoveToLocation(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack);

	UFUNCTION(Server, Unreliable, WithValidation, Category = "Unit Attack Move")
	void Server_UnitFreedomAttackMoveToLocation(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack);
	virtual bool Server_UnitFreedomAttackMoveToLocation_Validate(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack);

	UFUNCTION(Client, Unreliable, Category = "Unit Attack Move")
	void Client_UnitFreedomAttackMoveToLocation(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack);

	//巡逻

	UFUNCTION(BlueprintCallable, Category = "Unit Patrol")
	void UnitPatrol(AActor* TargetUnit, const TArray<FVector>& InPoints);

	UFUNCTION(Server, Unreliable, WithValidation, Category = "Unit Patrol")
	void Server_UnitPatrol(AActor* TargetUnit, const TArray<FVector>& InPoints);
	virtual bool Server_UnitPatrol_Validate(AActor* TargetUnit, const TArray<FVector>& InPoints);

	UFUNCTION(Client, Unreliable, Category = "Unit Patrol")
	void Client_UnitPatrol(AActor* TargetUnit, const TArray<FVector>& InPoints);


	//释放技能函数
	UFUNCTION(BlueprintCallable, Category = "Unit Release Skill")
	void UnitReleaseSkill(AActor* TargetUnit, int InSkillIndex);

	UFUNCTION(Server, Unreliable, WithValidation, Category = "Unit Release Skill")
	void Server_UnitReleaseSkill(AActor* TargetUnit, int InSkillIndex);
	virtual bool Server_UnitReleaseSkill_Validate(AActor* TargetUnit, int InSkillIndex);

	UFUNCTION(Client, Unreliable, Category = "Unit Release Skill")
	void Client_UnitReleaseSkill(AActor* TargetUnit, int InSkillIndex);
};
