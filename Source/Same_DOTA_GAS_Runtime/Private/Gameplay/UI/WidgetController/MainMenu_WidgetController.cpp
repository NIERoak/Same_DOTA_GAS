// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/UI/WidgetController/MainMenu_WidgetController.h"


void UMainMenu_WidgetController::BroadcastInitiaValues()
{
	
	const USame_DOTA_AttributeSet* NewAS = CastChecked<USame_DOTA_AttributeSet>(Current_AttributeSet);
	
	OnCharLevelChanged.Broadcast(NewAS->GetCharLevel());
	OnExperienceChanged.Broadcast(NewAS->GetExperience());
	OnMaxExperienceChanged.Broadcast(NewAS->GetMaxExperience());
	OnHealthChanged.Broadcast(NewAS->GetHealth());
	OnMaxHealthChanged.Broadcast(NewAS->GetMaxHealth());
	OnHealthRecoveryRateChanged.Broadcast(NewAS->GetHealthRecoveryRate());
	OnManaChanged.Broadcast(NewAS->GetMana());
	OnMaxManaChanged.Broadcast(NewAS->GetMaxMana());
	OnManaRecoveryRateChanged.Broadcast(NewAS->GetManaRecoveryRate());
	OnAttackChanged.Broadcast(NewAS->GetAttack());
	OnMinAttackIntervalChanged.Broadcast(NewAS->GetMinAttackInterval());
	OnAttackSpeedChanged.Broadcast(NewAS->GetAttackSpeed());
	OnAttackRangeChanged.Broadcast(NewAS->GetAttackRange());
	OnEnhancedCastingDistanceChanged.Broadcast(NewAS->GetEnhancedCastingDistance());
	OnDefenseChanged.Broadcast(NewAS->GetDefense());
	OnMagicResistanceChanged.Broadcast(NewAS->GetMagicResistance());
	OnMoveSpeedChanged.Broadcast(NewAS->GetMoveSpeed());

}

void UMainMenu_WidgetController::BindCallbacksToDependencies()
{
	
	if (Current_AttributeSet != nullptr)
	{
		const USame_DOTA_AttributeSet* NewAS = CastChecked<USame_DOTA_AttributeSet>(Current_AttributeSet);		

		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetCharLevelAttribute()).AddUObject(this, &UMainMenu_WidgetController::CharLevelchanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetExperienceAttribute()).AddUObject(this, &UMainMenu_WidgetController::Experiencechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxExperienceAttribute()).AddUObject(this, &UMainMenu_WidgetController::MaxExperiencechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetHealthAttribute()).AddUObject(this, &UMainMenu_WidgetController::Healthchanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxHealthAttribute()).AddUObject(this, &UMainMenu_WidgetController::MaxHealthchanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetHealthRecoveryRateAttribute()).AddUObject(this, &UMainMenu_WidgetController::HealthRecoveryRatechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetManaAttribute()).AddUObject(this, &UMainMenu_WidgetController::Manachanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxManaAttribute()).AddUObject(this, &UMainMenu_WidgetController::MaxManachanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetManaRecoveryRateAttribute()).AddUObject(this, &UMainMenu_WidgetController::ManaRecoveryRatechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetAttackAttribute()).AddUObject(this, &UMainMenu_WidgetController::Attackchanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMinAttackIntervalAttribute()).AddUObject(this, &UMainMenu_WidgetController::MinAttackIntervalchanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetAttackSpeedAttribute()).AddUObject(this, &UMainMenu_WidgetController::AttackSpeedchanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetAttackRangeAttribute()).AddUObject(this, &UMainMenu_WidgetController::AttackRangechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetEnhancedCastingDistanceAttribute()).AddUObject(this, &UMainMenu_WidgetController::EnhancedCastingDistancechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetDefenseAttribute()).AddUObject(this, &UMainMenu_WidgetController::Defensechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMagicResistanceAttribute()).AddUObject(this, &UMainMenu_WidgetController::MagicResistancechanged);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMoveSpeedAttribute()).AddUObject(this, &UMainMenu_WidgetController::MoveSpeedchanged);
		
	}		

}

void UMainMenu_WidgetController::UnBindCallbacksToDependencies()
{

	if (Current_AttributeSet != nullptr)
	{
		const USame_DOTA_AttributeSet* NewAS = CastChecked<USame_DOTA_AttributeSet>(Current_AttributeSet);

		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetCharLevelAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetExperienceAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxExperienceAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetHealthAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxHealthAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetHealthRecoveryRateAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetManaAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMaxManaAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetManaRecoveryRateAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetAttackAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMinAttackIntervalAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetAttackSpeedAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetAttackRangeAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetEnhancedCastingDistanceAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetDefenseAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMagicResistanceAttribute()).RemoveAll(this);
		Current_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(NewAS->GetMoveSpeedAttribute()).RemoveAll(this);
	}
	
}

void UMainMenu_WidgetController::CharLevelchanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnCharLevelChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnCharLevelChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::Experiencechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnExperienceChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnExperienceChanged.Broadcast(0.f);
	}
}


void UMainMenu_WidgetController::MaxExperiencechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnMaxExperienceChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMaxExperienceChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::Healthchanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnHealthChanged.Broadcast(Data.NewValue);		
	}
	else
	{
		OnHealthChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::MaxHealthchanged(const FOnAttributeChangeData& Data) const
{
	
	if (Current_AttributeSet != nullptr)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMaxHealthChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::HealthRecoveryRatechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnHealthRecoveryRateChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnHealthRecoveryRateChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::Manachanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnManaChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::MaxManachanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMaxManaChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::ManaRecoveryRatechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnManaRecoveryRateChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnManaRecoveryRateChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::Attackchanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnAttackChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnAttackChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::MinAttackIntervalchanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnMinAttackIntervalChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMinAttackIntervalChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::AttackSpeedchanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnAttackSpeedChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnAttackSpeedChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::AttackRangechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnAttackRangeChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnAttackRangeChanged.Broadcast(0.f);
	}

}

void UMainMenu_WidgetController::EnhancedCastingDistancechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnEnhancedCastingDistanceChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnEnhancedCastingDistanceChanged.Broadcast(0.f);
	}

}

void UMainMenu_WidgetController::Defensechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnDefenseChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnDefenseChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::MagicResistancechanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnMagicResistanceChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMagicResistanceChanged.Broadcast(0.f);
	}
}

void UMainMenu_WidgetController::MoveSpeedchanged(const FOnAttributeChangeData& Data) const
{
	if (Current_AttributeSet != nullptr)
	{
		OnMoveSpeedChanged.Broadcast(Data.NewValue);
	}
	else
	{
		OnMoveSpeedChanged.Broadcast(0.f);
	}
}
