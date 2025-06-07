#pragma once

#include "Coreminimal.h"
#include "UObject/Object.h"

#include "GAS/Same_DOTA_AbilitySystemComponent.h"
#include "GAS/Same_DOTA_AttributeSet.h"

#include "Gameplay/Same_DOTA_CharacterBase.h"

#include "WidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMainMenuUpdatedSignature, bool, bUpdated);


class UAbilitySystemComponent;
class UAttributeSet;



UCLASS(BlueprintType, Blueprintable)
class SAME_DOTA_GAS_RUNTIME_API UWidgetController :public UObject
{
	GENERATED_BODY()

public:
	
	UWidgetController();

	UFUNCTION(BlueprintCallable)
	void SetPlayerController(APlayerController* InPC);
	
	UFUNCTION(BlueprintCallable)
	void UpdateSelectedUnit();
	//�㲥��ʼ��������ֵ
	virtual void BroadcastInitiaValues();
	//�����Լ��仯��ֵ
	virtual void BindCallbacksToDependencies();
	//������Ա仯ί��
	virtual void UnBindCallbacksToDependencies();

public:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<ASame_DOTA_CharacterBase> Current_SelectedActor;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> Current_PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> Current_AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> Current_AttributeSet;

protected:
	TObjectPtr<UAbilitySystemComponent> Empty_AbilitySystemComponent;

	TObjectPtr<UAttributeSet> Empty_AttributeSet;

public:
	UPROPERTY(BlueprintAssignable, Category = "GAS Attrubutes")
	FOnMainMenuUpdatedSignature OnMainMenuUpdated;
};