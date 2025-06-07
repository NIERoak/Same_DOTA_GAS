// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"



#include "Same_DOTA_HUD.generated.h"



/**
 * 
 */

class USame_DOTA_BaseUserWidget;
class UMainMenu_WidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class SAME_DOTA_GAS_RUNTIME_API ASame_DOTA_HUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ASame_DOTA_HUD();
		
	
	UPROPERTY(BlueprintReadWrite, Category = "Paint")
	FVector2D StartPointLocation;//视口上方框起始点2D坐标

	UPROPERTY(BlueprintReadWrite, Category = "Paint")
	FVector2D EndPointLocation;//视口上方框结束点2D坐标
	
	//绘画框变量		
	UFUNCTION(BlueprintCallable, Category = "Draw Box")
	void StartDrawBoxOnScreen(bool bPressd, FVector StartLocation);
	
	//重写父类中的绘画事件
	virtual void DrawHUD() override;		
	

protected:

	virtual void BeginPlay() override;



public:
	UPROPERTY()
	TObjectPtr<USame_DOTA_BaseUserWidget> MainMenuWidget_Ref;

	UMainMenu_WidgetController* GetMainMenu_WidgetController();

	void InitMainMenu();
	
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void UpdateMainMenu();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USame_DOTA_BaseUserWidget> MainMenuWidget_Class;//蓝图必填

	UPROPERTY()
	TObjectPtr<UMainMenu_WidgetController> MainMenu_WidgetController_Ref;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenu_WidgetController> MainMenu_WidgetController_Class;//蓝图必填
};
