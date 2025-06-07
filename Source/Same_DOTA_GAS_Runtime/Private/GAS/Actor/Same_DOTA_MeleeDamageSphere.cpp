// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Actor/Same_DOTA_MeleeDamageSphere.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


#define ECC_PluginCustomObject ECC_Selected_Unit

ASame_DOTA_MeleeDamageSphere::ASame_DOTA_MeleeDamageSphere()
{
	bReplicates = false;
}

void ASame_DOTA_MeleeDamageSphere::BeginPlay()
{
	Super::BeginPlay();
	ApplyDamage();
}

void ASame_DOTA_MeleeDamageSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASame_DOTA_MeleeDamageSphere::ApplyDamage()
{
	
	float Radius = OwnerActor->GetAttributeSet()->GetAttackRange();

	FVector StartPointlocation = OwnerActor->GetActorLocation();
	FVector EndPointLocation = StartPointlocation;

	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(Unit) };

	const bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		StartPointlocation,
		EndPointLocation,
		Radius,		
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHits,
		true,
		FColor::Green,
		FColor::Red,
		0.0f);

	if (bHit)
	{
		bool bHitTagetActor = false;

		for (const FHitResult& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			if (ASame_DOTA_CharacterBase* SelectedActor = Cast<ASame_DOTA_CharacterBase>(HitActor))
			{
				if (SelectedActor == TagetActor)
				{
					bHitTagetActor = true;
				}
			}
		}

		if (bHitTagetActor)
		{		
			
			TagetActor->GetAbilitySystemComponent()->ReceiveGamaplayEffectDamage(OwnerActor, AblityType_DamageType, Damage);
			UE_LOG(LogTemp,Warning,TEXT("bHitTagetActor"));
		}
	}
}
