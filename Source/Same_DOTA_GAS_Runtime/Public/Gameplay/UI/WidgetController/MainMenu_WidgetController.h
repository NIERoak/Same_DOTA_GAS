// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/UI/WidgetController/WidgetController.h"


#include "MainMenu_WidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharLevelChangedSignature, float, NewCharLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExperiencelChangedSignature, float, NewExperience);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxExperienceChangedSignature, float, NewMaxExperience);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthRecoveryRateChangedSignature, float, NewHealthRecoveryRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaRecoveryRateChangedSignature, float, NewManaRecoveryRate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackChangedSignature, float, NewAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinAttackIntervalChangedSignature, float, NewMinAttackInterval);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackSpeedChangedSignature, float, NewAttackSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackRangeChangedSignature, float, NewAttackRange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnhancedCastingDistanceChangedSignature, float, NewEnhancedCastingDistance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDefenseChangedSignature, float, NewDefense);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagicResistanceChangedSignature, float, NewMagicResistance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveSpeedChangedSignature, float, NewMoveSpeed);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class SAME_DOTA_GAS_RUNTIME_API UMainMenu_WidgetController : public UWidgetController
{
	GENERATED_BODY()

public:
	//广播初始化的属性值
	virtual void BroadcastInitiaValues() override;
	//绑定属性集变化的回调函数
	virtual void BindCallbacksToDependencies() override;
	//接触绑定回调函数
	virtual void UnBindCallbacksToDependencies() override;


	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnCharLevelChangedSignature OnCharLevelChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnExperiencelChangedSignature OnExperienceChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMaxExperienceChangedSignature OnMaxExperienceChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHealthRecoveryRateChangedSignature OnHealthRecoveryRateChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnManaRecoveryRateChangedSignature OnManaRecoveryRateChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnAttackChangedSignature OnAttackChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMinAttackIntervalChangedSignature OnMinAttackIntervalChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnAttackSpeedChangedSignature OnAttackSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnAttackRangeChangedSignature OnAttackRangeChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnEnhancedCastingDistanceChangedSignature OnEnhancedCastingDistanceChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnDefenseChangedSignature OnDefenseChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMagicResistanceChangedSignature OnMagicResistanceChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMoveSpeedChangedSignature OnMoveSpeedChanged;

protected:
	//属性值实时改变的回调函数
	void CharLevelchanged(const FOnAttributeChangeData& Data) const;
	void Experiencechanged(const FOnAttributeChangeData& Data) const;
	void MaxExperiencechanged(const FOnAttributeChangeData& Data) const;
	
	void Healthchanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthchanged(const FOnAttributeChangeData& Data) const;
	void HealthRecoveryRatechanged(const FOnAttributeChangeData& Data) const;

	void Manachanged(const FOnAttributeChangeData& Data) const;
	void MaxManachanged(const FOnAttributeChangeData& Data) const;
	void ManaRecoveryRatechanged(const FOnAttributeChangeData& Data) const;

	void Attackchanged(const FOnAttributeChangeData& Data) const;
	void MinAttackIntervalchanged(const FOnAttributeChangeData& Data) const;
	void AttackSpeedchanged(const FOnAttributeChangeData& Data) const;

	void AttackRangechanged(const FOnAttributeChangeData& Data) const;
	void EnhancedCastingDistancechanged(const FOnAttributeChangeData& Data) const;

	void Defensechanged(const FOnAttributeChangeData& Data) const;
	void MagicResistancechanged(const FOnAttributeChangeData& Data) const;

	void MoveSpeedchanged(const FOnAttributeChangeData& Data) const;
};
