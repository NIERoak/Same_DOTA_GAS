

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "Same_DOTA_WidgetComponent.generated.h"

class ASame_DOTA_CharacterBase;
class USame_DOTA_HPBarWidget;

UCLASS()
class SAME_DOTA_GAS_RUNTIME_API USame_DOTA_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget Component")
	TObjectPtr<USame_DOTA_HPBarWidget> HPBarWidget_Ref;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget Component")
	TObjectPtr<ASame_DOTA_CharacterBase> OwnerChararacter_Ref;
	
	
	UFUNCTION(BlueprintCallable, Category = "Widget Component")
	void SetCustomWidget_Ref();

	UFUNCTION(BlueprintCallable, Category = "Widget Component")
	USame_DOTA_HPBarWidget* GetCustomWidget_Ref();

	UFUNCTION(BlueprintCallable, Category = "Widget Component")
	void SetOwnerCharacterRef(AActor* InOwnerChar);

};
