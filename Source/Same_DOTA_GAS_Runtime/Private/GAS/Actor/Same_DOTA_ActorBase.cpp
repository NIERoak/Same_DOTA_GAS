// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Actor/Same_DOTA_ActorBase.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "GAS/Ability/Same_DOTA_GameplayAbilityBase.h"

// Sets default values
ASame_DOTA_ActorBase::ASame_DOTA_ActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASame_DOTA_ActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASame_DOTA_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASame_DOTA_ActorBase::SetOwnerActorTagetActorAndDamageType(ASame_DOTA_CharacterBase* InOwnerActor, ASame_DOTA_CharacterBase* InTagetActor, EAblityType_DamageType InAblityType_DamageType, float InDamage)
{
	OwnerActor = InOwnerActor;
	TagetActor = InTagetActor;
	AblityType_DamageType = InAblityType_DamageType;
	Damage = InDamage;
}





