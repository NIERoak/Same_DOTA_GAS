// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/UI/Widget/Same_DOTA_BaseUserWidget.h"
#include "Same_DOTA_HPBarWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPBarCharLevelChangedSignature, float, NewCharLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPBarHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPBarMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPBarManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHPBarMaxManaChangedSignature, float, NewMaxMana);



UCLASS()
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_HPBarWidget : public USame_DOTA_BaseUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HPBar Widget")
	TObjectPtr<ASame_DOTA_CharacterBase> OwnerChararacter_Ref;

	UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	//�㲥��ʼ��������ֵ
	void BroadcastInitiaValues();
	//�����Լ��仯��ֵ
	void BindCallbacksToDependencies();



	UFUNCTION(BlueprintCallable, Category = "HPBar Widget")
	void SetWidgetOwnerCharacterRef(AActor* InOwnerChar);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetOwnerCharacterRefSet();//��ͼȥ���ð�UI�����¼�




	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHPBarCharLevelChangedSignature OnCharLevelChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHPBarHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHPBarMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHPBarManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnHPBarMaxManaChangedSignature OnMaxManaChanged;



protected:
	//����ֵʵʱ�ı�Ļص�����
	void CharLevelChanged(const FOnAttributeChangeData& Data) const;

	void Healthchanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthchanged(const FOnAttributeChangeData& Data) const;

	void Manachanged(const FOnAttributeChangeData& Data) const;
	void MaxManachanged(const FOnAttributeChangeData& Data) const;



};