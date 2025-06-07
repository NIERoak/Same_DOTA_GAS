// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "Same_DOTA_AttributeSet.generated.h"

//重要：批量处理属性值宏
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS(BlueprintType)
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	USame_DOTA_AttributeSet();
	//使用复制功能必须实现的注册函数
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//属性改变前调用
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//属性改变后调用
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//角色等级
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CharLevel, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData CharLevel;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, CharLevel)

		UFUNCTION()
	void OnRep_CharLevel(const FGameplayAttributeData& OldCharLevel) const;

	//经验值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Experience, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, Experience)

		UFUNCTION()
	void OnRep_Experience(const FGameplayAttributeData& OldExperience) const;

	//最大经验值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxExperience, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, MaxExperience)

		UFUNCTION()
	void OnRep_MaxExperience(const FGameplayAttributeData& OldMaxExperience) const;

	//生命值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, Health)

		UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	//生命值上限
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, MaxHealth)

		UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	//生命值回复速率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRecoveryRate, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData HealthRecoveryRate;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, HealthRecoveryRate)

		UFUNCTION()
	void OnRep_HealthRecoveryRate(const FGameplayAttributeData& OldHealthRecoveryRate) const;

	//魔法值
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, Mana)

		UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	//魔法值上限
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, MaxMana)
		
		UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	//魔法值回复速率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRecoveryRate, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData ManaRecoveryRate;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, ManaRecoveryRate)

		UFUNCTION()
	void OnRep_ManaRecoveryRate(const FGameplayAttributeData& OldManaRecoveryRate) const;

	//攻击力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, Attack)

		UFUNCTION()
	void OnRep_Attack(const FGameplayAttributeData& OldAttack) const;

	//最小攻击间隔
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MinAttackInterval, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData MinAttackInterval;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, MinAttackInterval)

		UFUNCTION()
	void OnRep_MinAttackInterval(const FGameplayAttributeData& OldMinAttackInterval) const;

	//攻击速度
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, AttackSpeed)

		UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;
	//攻击距离
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackRange, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData AttackRange;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, AttackRange)

		UFUNCTION()
	void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange) const;
	//施法距离增加
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_EnhancedCastingDistance, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData EnhancedCastingDistance;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, EnhancedCastingDistance)

		UFUNCTION()
	void OnRep_EnhancedCastingDistance(const FGameplayAttributeData& OldEnhancedCastingDistance) const;

	//防御力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, Defense)

		UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldDefense) const;

	//魔法抗性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, MagicResistance)

		UFUNCTION()
	void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;

	//移动速度
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, meta = (ClampMin = 0), Category = "Vital Attribute")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(USame_DOTA_AttributeSet, MoveSpeed)

		UFUNCTION()
	void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const;
};
