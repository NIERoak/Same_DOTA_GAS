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
	FVector2D StartPointLocation;//�ӿ��Ϸ�����ʼ��2D����

	UPROPERTY(BlueprintReadWrite, Category = "Paint")
	FVector2D EndPointLocation;//�ӿ��Ϸ��������2D����
	
	//�滭�����		
	UFUNCTION(BlueprintCallable, Category = "Draw Box")
	void StartDrawBoxOnScreen(bool bPressd, FVector StartLocation);
	
	//��д�����еĻ滭�¼�
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
	TSubclassOf<USame_DOTA_BaseUserWidget> MainMenuWidget_Class;//��ͼ����

	UPROPERTY()
	TObjectPtr<UMainMenu_WidgetController> MainMenu_WidgetController_Ref;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenu_WidgetController> MainMenu_WidgetController_Class;//��ͼ����
};
