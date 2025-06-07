// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Same_DOTA_CameraPawn.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "Gameplay/Interface/Same_DOTA_TemplateInterface.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"




// Sets default values
ASame_DOTA_CameraPawn::ASame_DOTA_CameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASame_DOTA_CameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASame_DOTA_CameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASame_DOTA_CameraPawn::UnitBaseMoveToLocation(AActor* TargetUnit, FVector InLocation, AActor* HitActor)
{
	if (HasAuthority())
	{
		Client_UnitBaseMoveToLocation(TargetUnit, InLocation, HitActor);
	}
	else
	{
		Server_UnitBaseMoveToLocation(TargetUnit, InLocation, HitActor);
	}
}

bool ASame_DOTA_CameraPawn::Server_UnitBaseMoveToLocation_Validate(AActor* TargetUnit, FVector InLocation, AActor* HitActor)
{
	return TargetUnit != nullptr && InLocation.ContainsNaN() == false;
}


void ASame_DOTA_CameraPawn::Server_UnitBaseMoveToLocation_Implementation(AActor* TargetUnit, FVector InLocation, AActor* HitActor)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			ISame_DOTA_TemplateInterface::Execute_UnitMoveTo(TargetUnit, InLocation, HitActor);
		}

	}
}

void ASame_DOTA_CameraPawn::Client_UnitBaseMoveToLocation_Implementation(AActor* TargetUnit, FVector InLocation, AActor* HitActor)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			ISame_DOTA_TemplateInterface::Execute_UnitMoveTo(TargetUnit, InLocation, HitActor);
		}
	}
}





//×ÔÓÉ¹¥»÷ÒÆ¶¯
void ASame_DOTA_CameraPawn::UnitFreedomAttackMoveToLocation(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack)
{
	if (HasAuthority())
	{
		Client_UnitFreedomAttackMoveToLocation(TargetUnit, InLocation, bFreedomAttack);
	}
	else
	{
		Server_UnitFreedomAttackMoveToLocation(TargetUnit, InLocation, bFreedomAttack);
	}
}

bool ASame_DOTA_CameraPawn::Server_UnitFreedomAttackMoveToLocation_Validate(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack)
{
	return TargetUnit != nullptr && InLocation.ContainsNaN() == false;
}

void ASame_DOTA_CameraPawn::Server_UnitFreedomAttackMoveToLocation_Implementation(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			ISame_DOTA_TemplateInterface::Execute_UnitAttackMoveTo(TargetUnit, InLocation, bFreedomAttack);
		}
	}
}

void ASame_DOTA_CameraPawn::Client_UnitFreedomAttackMoveToLocation_Implementation(AActor* TargetUnit, FVector InLocation, bool bFreedomAttack)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			ISame_DOTA_TemplateInterface::Execute_UnitAttackMoveTo(TargetUnit, InLocation, bFreedomAttack);
		}
	}
}



//Ñ²Âß
void ASame_DOTA_CameraPawn::UnitPatrol(AActor* TargetUnit, const TArray<FVector>& InPoints)
{
	if (HasAuthority())
	{
		Client_UnitPatrol(TargetUnit, InPoints);
	}
	else
	{
		Server_UnitPatrol(TargetUnit, InPoints);
	}
}

bool ASame_DOTA_CameraPawn::Server_UnitPatrol_Validate(AActor* TargetUnit, const TArray<FVector>& InPoints)
{
	return TargetUnit != nullptr && InPoints.Num() > 0;
}

void ASame_DOTA_CameraPawn::Server_UnitPatrol_Implementation(AActor* TargetUnit, const TArray<FVector>& InPoints)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			TArray<FVector> ArrayTemp;
			for (FVector Temp : InPoints)
			{
				ArrayTemp.AddUnique(Temp);
			}

			ISame_DOTA_TemplateInterface::Execute_UnitPatrol(TargetUnit, ArrayTemp);
		}
	}
}

void ASame_DOTA_CameraPawn::Client_UnitPatrol_Implementation(AActor* TargetUnit, const TArray<FVector>& InPoints)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			TArray<FVector> ArrayTemp;
			for (FVector Temp : InPoints)
			{
				ArrayTemp.AddUnique(Temp);
			}			
			
			ISame_DOTA_TemplateInterface::Execute_UnitPatrol(TargetUnit, ArrayTemp);
		}
	}
}









void ASame_DOTA_CameraPawn::UnitReleaseSkill(AActor* TargetUnit,int InSkillIndex)
{
	if (HasAuthority())
	{
		Client_UnitReleaseSkill(TargetUnit,InSkillIndex);
	}
	else
	{
		Server_UnitReleaseSkill(TargetUnit,InSkillIndex);
	}
}

bool ASame_DOTA_CameraPawn::Server_UnitReleaseSkill_Validate(AActor* TargetUnit, int InSkillIndex)
{
	return true;
}

void ASame_DOTA_CameraPawn::Server_UnitReleaseSkill_Implementation(AActor* TargetUnit,int InSkillIndex)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			ISame_DOTA_TemplateInterface::Execute_TryReleaseSkill(TargetUnit, InSkillIndex);
		}
	}
}

void ASame_DOTA_CameraPawn::Client_UnitReleaseSkill_Implementation(AActor* TargetUnit,int InSkillIndex)
{
	if (TargetUnit)
	{
		if (TargetUnit->GetClass()->ImplementsInterface(USame_DOTA_TemplateInterface::StaticClass()))
		{
			ISame_DOTA_TemplateInterface::Execute_TryReleaseSkill(TargetUnit, InSkillIndex);
		}
	}
}



