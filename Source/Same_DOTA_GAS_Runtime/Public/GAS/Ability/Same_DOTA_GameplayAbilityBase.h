// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "Same_DOTA_GameplayAbilityBase.generated.h"


UENUM(BlueprintType)
enum class EAblityType_LoadType :uint8
{
	None,
	Melee,
	Skill,
	Item,	
};

UENUM(BlueprintType)
enum class EAblityType_MeleeType :uint8
{
	None,
	ShortDistance,
	LongDistance,	
};

UENUM(BlueprintType)
enum class EAblityType_Type :uint8
{
	None,
	Actived,
	Passived,
	
};

UENUM(BlueprintType)
enum class EAblityType_ActivelyTrigger :uint8
{
	None,
	Directly,
	ChooseTarget,
	ChooseLocation,
	ChooseDirection,
	ContinuouslyCasting,
	
};

UENUM(BlueprintType)
enum class EAblityType_PassivelyTrigger :uint8
{
	None,
	Self_Directly,
	Self_AfterAttacking,
	Self_AfterCasting,
	FromEnemy_UnderAttack,
	FromEnemy_UnderMagic,
	FromEnemy_UnderDamage,
	Self_Stack,
	
};

UENUM(BlueprintType)
enum class EAblityType_EffectedType :uint8
{
	None,
	OneTarget,
	AOE,
};

UENUM(BlueprintType)
enum class EAblityType_EffectedUnit :uint8
{
	None,
	Enemy,
	Self,
	Friend,
	Self_Friend,
	All,	
};

UENUM(BlueprintType)
enum class EAblityType_Cost :uint8
{
	None,
	HP,
	MP,	
};

UENUM(BlueprintType)
enum class EAblityType_DamageType :uint8
{
	None,
	PhysicalDamage,
	MagicDamage,
	RealDamage,
};


USTRUCT(BlueprintType)
struct FGamepalyAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_LoadType AblityType_LoadType;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_Type AblityType_Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_ActivelyTrigger AblityType_ActivelyTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_PassivelyTrigger AblityType_PassivelyTrigger;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_EffectedType AblityType_EffectedType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_EffectedUnit AblityType_EffectedUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	FGameplayTagContainer CoolDownEffect_Tags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	float CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_Cost AblityType_Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	EAblityType_DamageType AblityType_DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	float CostValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	UTexture2D* AbilityIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Info")
	TSubclassOf<USame_DOTA_GameplayAbilityBase> Ability_Class;


	FGamepalyAbilityInfo();
	FGamepalyAbilityInfo(
		EAblityType_LoadType InAblityType_LoadType,
		EAblityType_Type InAblityType_Type, 
		EAblityType_ActivelyTrigger InAblityType_ActivelyTrigger, 
		EAblityType_PassivelyTrigger InAblityType_PassivelyTrigger, 
		EAblityType_EffectedType InAblityType_EffectedType,
		EAblityType_EffectedUnit InAblityType_EffectedUnit,
		FGameplayTagContainer InCoolDownEffect_Tags,float InCoolDown, 
		EAblityType_Cost InAblityType_Cost,
		EAblityType_DamageType InAblityType_DamageType,
		float InCostValue, 
		UTexture2D* InAbilityIcon, 
		TSubclassOf<USame_DOTA_GameplayAbilityBase> InAbility_Class);
};


class ASame_DOTA_CharacterBase;

UCLASS()
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()


public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	//API
	virtual void InitAbilityInfo();

public:
	//Intilize
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetSkillIndex(int InIndex);
	int SkillIndex = 0;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetItemAbilityIndex(int InIndex);
	int ItemAbilityIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<ASame_DOTA_CharacterBase> OwnerActor = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	TObjectPtr<ASame_DOTA_CharacterBase> TargetActor = nullptr;

public:
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	EAblityType_LoadType AblityType_LoadType;
	
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	EAblityType_MeleeType AblityType_MeleeType;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "AblityType_LoadType != EAblityType_LoadType::None && AblityType_LoadType != EAblityType_LoadType::Melee"), Category = "Ability")
	EAblityType_Type AblityType_Type;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "AblityType_Type == EAblityType_Type::Actived"), Category = "Ability")
	EAblityType_ActivelyTrigger AblityType_ActivelyTrigger;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "AblityType_Type == EAblityType_Type::Passived"), Category = "Ability")
	EAblityType_PassivelyTrigger AblityType_PassivelyTrigger;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "AblityType_LoadType != EAblityType_LoadType::None && AblityType_LoadType != EAblityType_LoadType::Melee"), Category = "Ability")
	EAblityType_EffectedType AblityType_EffectedType;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "AblityType_LoadType != EAblityType_LoadType::None && AblityType_LoadType != EAblityType_LoadType::Melee"), Category = "Ability")
	EAblityType_EffectedUnit AblityType_EffectedUnit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	EAblityType_DamageType AblityType_DamageType;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "AblityType_LoadType != EAblityType_LoadType::None && AblityType_LoadType != EAblityType_LoadType::Melee"), Category = "Ability")
	UTexture2D* AbilityIcon;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FName SpawnActorSocketName;

public:

	UFUNCTION(BlueprintCallable, Category = "Ability")
	FGamepalyAbilityInfo GetAbilityInfo(int InLevel);	

	UFUNCTION(BlueprintPure, Category = "Ability")
	UAnimMontage* GetCharAnimationMontage();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FString GetCharMeleeAnimationMontageFragmentName();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FString GetCharReleaseSkillAnimationMontageFragmentName(int InSkillAnimationIndex);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void SetCharPlayingAnimationMontageCompleted();
};
