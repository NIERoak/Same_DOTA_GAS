// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/UI/Widget/Same_DOTA_BaseUserWidget.h"


void USame_DOTA_BaseUserWidget::SetWidgetController(UObject* InwidgetController)
{
	
	WidgetController = Cast<UWidgetController>(InwidgetController);
	//调用设置函数
	WidgetControllerSet();
}

UWidgetController* USame_DOTA_BaseUserWidget::GetWidgetController()
{
	if (WidgetController)
	{
		
		return WidgetController;
	}	
	return nullptr;
}
