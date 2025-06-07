// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay/UI/WidgetController/WidgetController.h"

#include "Same_DOTA_BaseUserWidget.generated.h"



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_BaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InwidgetController);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UWidgetController* GetWidgetController();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWidgetController> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();


};
