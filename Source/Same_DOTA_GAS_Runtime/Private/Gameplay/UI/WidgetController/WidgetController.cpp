#include "Gameplay/UI/WidgetController/WidgetController.h"

#include "Gameplay/Same_DOTA_PlayerController.h"




UWidgetController::UWidgetController()
{
	Empty_AbilitySystemComponent= CreateDefaultSubobject<USame_DOTA_AbilitySystemComponent>("AbilitySystemComponent");
	Empty_AttributeSet= CreateDefaultSubobject<USame_DOTA_AttributeSet>("AttributeSet");
	
}

void UWidgetController::SetPlayerController(APlayerController* InPC)
{
	Current_PlayerController = InPC;
}

void UWidgetController::UpdateSelectedUnit()
{
	if (ASame_DOTA_PlayerController* PC = Cast<ASame_DOTA_PlayerController>(Current_PlayerController))
	{
		UnBindCallbacksToDependencies();//������Ա仯�ص���
		
		if (!PC->Selected_UnitsSelf.IsEmpty())
		{
			ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(PC->Selected_UnitsSelf[0]);
			Current_SelectedActor = NewChar;
			Current_AbilitySystemComponent = NewChar->GetAbilitySystemComponent();
			Current_AttributeSet = NewChar->GetAttributeSet();
		}
		else if (PC->Selected_UnitFriend != nullptr)
		{
			ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(PC->Selected_UnitFriend);
			Current_SelectedActor = NewChar;
			Current_AbilitySystemComponent = NewChar->GetAbilitySystemComponent();
			Current_AttributeSet = NewChar->GetAttributeSet();
		}
		else if (PC->Selected_UnitEnemy != nullptr)
		{
			ASame_DOTA_CharacterBase* NewChar = Cast<ASame_DOTA_CharacterBase>(PC->Selected_UnitEnemy);
			Current_SelectedActor = NewChar;
			Current_AbilitySystemComponent = NewChar->GetAbilitySystemComponent();
			Current_AttributeSet = NewChar->GetAttributeSet();
		}
		else
		{
			Current_SelectedActor = nullptr;
			Current_AbilitySystemComponent = Empty_AbilitySystemComponent;
			Current_AttributeSet = Empty_AttributeSet;
		}

		BroadcastInitiaValues();//ÿ�θ��¿�ѡ��Ĳ�����Ҫ����һ��UI
		BindCallbacksToDependencies();//���°󶨻ص�
		OnMainMenuUpdated.Broadcast(true);//֪ͨUI���и���
		
	}
}

void UWidgetController::BroadcastInitiaValues()
{

}

void UWidgetController::BindCallbacksToDependencies()
{

}

void UWidgetController::UnBindCallbacksToDependencies()
{

}
