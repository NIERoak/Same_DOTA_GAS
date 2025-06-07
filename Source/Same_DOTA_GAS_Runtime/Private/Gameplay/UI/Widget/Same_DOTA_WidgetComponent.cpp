// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/UI/Widget/Same_DOTA_WidgetComponent.h"
#include "Gameplay/UI/Widget/HPBar_Widget/Same_DOTA_HPBarWidget.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"

void USame_DOTA_WidgetComponent::SetCustomWidget_Ref()
{
	if (GetWidgetClass())
	{
		if (USame_DOTA_HPBarWidget* WidgetObject = Cast<USame_DOTA_HPBarWidget>(GetUserWidgetObject()))
		{
			HPBarWidget_Ref = WidgetObject;			
		}
	}

}

USame_DOTA_HPBarWidget* USame_DOTA_WidgetComponent::GetCustomWidget_Ref()
{
	if (HPBarWidget_Ref)
	{
		return HPBarWidget_Ref;
	}	
	return nullptr;
	
}

void USame_DOTA_WidgetComponent::SetOwnerCharacterRef(AActor* InOwnerChar)
{
	if (InOwnerChar)
	{
		SetCustomWidget_Ref();
		if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(InOwnerChar))
		{
			OwnerChararacter_Ref = NewChar;

			
			if (HPBarWidget_Ref)
			{
				HPBarWidget_Ref->SetWidgetOwnerCharacterRef(NewChar);
			}			
		}
	}
	
}
