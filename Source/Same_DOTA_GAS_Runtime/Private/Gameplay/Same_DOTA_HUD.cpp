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


		FVector MouseStartWorldLocation = StartLocation;//需要转换成视口坐标

		APlayerController* PlayerController = GetOwningPlayerController();
		if (!PlayerController) return;

		

		FVector2D ScreenPosition;
		bool bIsProjectionValid;
		FVector TargetWorldLocation = MouseStartWorldLocation;//将鼠标点击的都一个世界坐标进行屏幕坐标转换
		// 执行坐标转换
		bIsProjectionValid = PlayerController->ProjectWorldLocationToScreen(
			TargetWorldLocation,
			ScreenPosition,//计算出的屏幕坐标
			false // 使用全局屏幕坐标而非分屏相对坐标
		);

		//处理屏幕缩放问题，计算出第一个点的正确屏幕坐标
		if (bIsProjectionValid)
		{
			//FVector2D ViewportSize;
			if (GEngine && GEngine->GameViewport)
			{
				//GEngine->GameViewport->GetViewportSize(ViewportSize);//视口大小

				float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());//视口缩放

				//计算正确的2D坐标
				StartPointLocation.X = ScreenPosition.X;
				StartPointLocation.Y = ScreenPosition.Y;

				float EndX;
				float EndY;
				if (PlayerController->GetMousePosition(EndX, EndY))
				{
					//设置当前鼠标位置，也就是结束点的坐标
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
	
	MainMenu_WidgetController_Ref->BroadcastInitiaValues();//广播一次初始化的属性值
	//MainMenu_WidgetController_Ref->BindCallbacksToDependencies();//绑定属性值实时变化的回调函数

	Widget->AddToViewport();

}

void ASame_DOTA_HUD::UpdateMainMenu()
{
	if (MainMenu_WidgetController_Ref)
	{
		MainMenu_WidgetController_Ref->UpdateSelectedUnit();
		
	}

}


