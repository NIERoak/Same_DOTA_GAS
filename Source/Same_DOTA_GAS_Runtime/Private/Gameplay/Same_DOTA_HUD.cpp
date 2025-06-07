// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Same_DOTA_HUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Gameplay/UI/Widget/Same_DOTA_BaseUserWidget.h"
#include "Gameplay/UI/WidgetController/MainMenu_WidgetController.h"


ASame_DOTA_HUD::ASame_DOTA_HUD()
{
   
}

void ASame_DOTA_HUD::DrawHUD()
{
	DrawRect(FLinearColor(1.0f,1.0f,1.0f,0.5f), StartPointLocation.X, StartPointLocation.Y, EndPointLocation.X - StartPointLocation.X, EndPointLocation.Y - StartPointLocation.Y);
}



void ASame_DOTA_HUD::StartDrawBoxOnScreen(bool bPressd, FVector StartLocation)
{
    
	if (bPressd)
	{


		FVector MouseStartWorldLocation = StartLocation;//��Ҫת�����ӿ�����

		APlayerController* PlayerController = GetOwningPlayerController();
		if (!PlayerController) return;

		

		FVector2D ScreenPosition;
		bool bIsProjectionValid;
		FVector TargetWorldLocation = MouseStartWorldLocation;//��������Ķ�һ���������������Ļ����ת��
		// ִ������ת��
		bIsProjectionValid = PlayerController->ProjectWorldLocationToScreen(
			TargetWorldLocation,
			ScreenPosition,//���������Ļ����
			false // ʹ��ȫ����Ļ������Ƿ����������
		);

		//������Ļ�������⣬�������һ�������ȷ��Ļ����
		if (bIsProjectionValid)
		{
			//FVector2D ViewportSize;
			if (GEngine && GEngine->GameViewport)
			{
				//GEngine->GameViewport->GetViewportSize(ViewportSize);//�ӿڴ�С

				float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());//�ӿ�����

				//������ȷ��2D����
				StartPointLocation.X = ScreenPosition.X;
				StartPointLocation.Y = ScreenPosition.Y;

				float EndX;
				float EndY;
				if (PlayerController->GetMousePosition(EndX, EndY))
				{
					//���õ�ǰ���λ�ã�Ҳ���ǽ����������
					EndPointLocation.X = EndX;
					EndPointLocation.Y = EndY;
					
				}
			}

		}
	}

	else
	{
		StartPointLocation.X = 0.f;
		StartPointLocation.Y = 0.f;

		EndPointLocation.X = 0.f;
		EndPointLocation.Y = 0.f;
	}
}

void ASame_DOTA_HUD::BeginPlay()
{
	Super::BeginPlay();

	InitMainMenu();
}

UMainMenu_WidgetController* ASame_DOTA_HUD::GetMainMenu_WidgetController()
{	
	return MainMenu_WidgetController_Ref;
}

void ASame_DOTA_HUD::InitMainMenu()
{
		
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidget_Class);
				
	
	MainMenu_WidgetController_Ref = NewObject<UMainMenu_WidgetController>(this, MainMenu_WidgetController_Class);
	MainMenu_WidgetController_Ref->SetPlayerController(GetOwningPlayerController());

	MainMenuWidget_Ref = Cast<USame_DOTA_BaseUserWidget>(Widget);	
	MainMenuWidget_Ref->SetWidgetController(MainMenu_WidgetController_Ref);
	
	MainMenu_WidgetController_Ref->BroadcastInitiaValues();//�㲥һ�γ�ʼ��������ֵ
	//MainMenu_WidgetController_Ref->BindCallbacksToDependencies();//������ֵʵʱ�仯�Ļص�����

	Widget->AddToViewport();

}

void ASame_DOTA_HUD::UpdateMainMenu()
{
	if (MainMenu_WidgetController_Ref)
	{
		MainMenu_WidgetController_Ref->UpdateSelectedUnit();
		
	}

}


