// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/UI/Widget/HPBar_Widget/Same_DOTA_HPBarWidget.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"

void USame_DOTA_HPBarWidget::BroadcastInitiaValues()
{
	const USame_DOTA_AttributeSet* NewAS = CastChecked<USame_DOTA_AttributeSet>(AttributeSet);

	OnCharLevelChanged.Broadcast(NewAS->GetCharLevel());
	
	OnHealthChanged.Broadcast(NewAS->GetHealth());
	OnMaxHealthChanged.Broadcast(NewAS->GetMaxHealth());

	OnManaChanged.Broadcast(NewAS->GetMana());
	OnMaxManaChanged.Broadcast(NewAS->GetMaxMana());
	
	
}

void USame_DOTA_HPBarWidget::BindCallbacksToDependencies()
{
	if (AttributeSet != nullptr)
	{
		const USame_DOTA_AttributeSet* NewAS = CastChecked<USame_DOTA_AttributeSet>(AttributeSet);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetCharLevelAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetHealthAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxHealthAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetManaAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxManaAttribute()).RemoveAll(this);
		
		

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetCharLevelAttribute()).AddUObject(this, &USame_DOTA_HPBarWidget::CharLevelChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetHealthAttribute()).AddUObject(this, &USame_DOTA_HPBarWidget::Healthchanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxHealthAttribute()).AddUObject(this, &USame_DOTA_HPBarWidget::MaxHealthchanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetManaAttribute()).AddUObject(this, &USame_DOTA_HPBarWidget::Manachanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxManaAttribute()).AddUObject(this, &USame_DOTA_HPBarWidget::MaxManachanged);			

	}

}

void USame_DOTA_HPBarWidget::SetWidgetOwnerCharacterRef(AActor* InOwnerChar)
{
	if (ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(InOwnerChar))
	{
		OwnerChararacter_Ref = NewChar;		
		AbilitySystemComponent = NewChar->GetAbilitySystemComponent();
		AttributeSet = NewChar->GetAttributeSet();

		WidgetOwnerCharacterRefSet();
		BroadcastInitiaValues();
		BindCallbacksToDependencies();


	}
}

void USame_DOTA_HPBarWidget::CharLevelChanged(const FOnAttributeChangeData& Data) const
{
	if (AttributeSet != nullptr)
	{
		OnCharLevelChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnCharLevelChanged.Broadcast(0.f);
	}
}

void USame_DOTA_HPBarWidget::Healthchanged(const FOnAttributeChangeData& Data) const
{
	if (AttributeSet != nullptr)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnHealthChanged.Broadcast(0.f);
	}
}

void USame_DOTA_HPBarWidget::MaxHealthchanged(const FOnAttributeChangeData& Data) const
{
	if (AttributeSet != nullptr)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMaxHealthChanged.Broadcast(0.f);
	}
}

void USame_DOTA_HPBarWidget::Manachanged(const FOnAttributeChangeData& Data) const
{
	if (AttributeSet != nullptr)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnManaChanged.Broadcast(0.f);
	}
}

void USame_DOTA_HPBarWidget::MaxManachanged(const FOnAttributeChangeData& Data) const
{
	if (AttributeSet != nullptr)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMaxManaChanged.Broadcast(0.f);
	}
}
