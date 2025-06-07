// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/GA/Same_DOTA_Melee_LongD_Template.h"
#include "Gameplay/Same_DOTA_CharacterBase.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Kismet/KismetMathLibrary.h"





USame_DOTA_Melee_LongD_Template::USame_DOTA_Melee_LongD_Template()
{
	AblityType_LoadType = EAblityType_LoadType::Melee;
	AblityType_MeleeType = EAblityType_MeleeType::LongDistance;
}

void USame_DOTA_Melee_LongD_Template::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		PlayAnimationMontage();
	}	
}

void USame_DOTA_Melee_LongD_Template::InitAbilityInfo()
{

}

void USame_DOTA_Melee_LongD_Template::PlayAnimationMontage()
{
	UAnimMontage* MontageToPlay = GetCharAnimationMontage();

	FName MontageFragment = FName(GetCharMeleeAnimationMontageFragmentName());	

	UAbilityTask_PlayMontageAndWait* PlayMontageTask =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			MontageToPlay,
			1.0f,   // 播放速率
			MontageFragment,
			false,  // 是否停止当能力结束时
			1.0f    // 动画开始时间
		);

	UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		FGameplayTag::RequestGameplayTag(FName("Ability.Melee.Event.Shoot"))
	);
	WaitEventTask->EventReceived.AddDynamic(this, &USame_DOTA_Melee_LongD_Template::OnShootEvent);
	WaitEventTask->ReadyForActivation();


	PlayMontageTask->OnCompleted.AddDynamic(this, &USame_DOTA_Melee_LongD_Template::OnMontageCompleted);
	PlayMontageTask->OnBlendOut.AddDynamic(this, &USame_DOTA_Melee_LongD_Template::OnMontageBlendOut);
	PlayMontageTask->OnInterrupted.AddDynamic(this, &USame_DOTA_Melee_LongD_Template::OnMontageInterrupted);
	PlayMontageTask->OnCancelled.AddDynamic(this, &USame_DOTA_Melee_LongD_Template::OnMontageCancelled);

	PlayMontageTask->ReadyForActivation();
	
}




void USame_DOTA_Melee_LongD_Template::OnMontageCompleted()
{
	SetCharPlayingAnimationMontageCompleted();
}

void USame_DOTA_Melee_LongD_Template::OnMontageCancelled()
{
	SetCharPlayingAnimationMontageCompleted();
}

void USame_DOTA_Melee_LongD_Template::OnMontageBlendOut()
{
	SetCharPlayingAnimationMontageCompleted();
}

void USame_DOTA_Melee_LongD_Template::OnMontageInterrupted()
{
	SetCharPlayingAnimationMontageCompleted();
}

void USame_DOTA_Melee_LongD_Template::OnShootEvent(const FGameplayEventData Payload)
{
	SpawnProjectileActor();
}

void USame_DOTA_Melee_LongD_Template::SpawnProjectileActor()
{
	if (!GetOwningActorFromActorInfo()->HasAuthority()) { return; };

	if (Projectile_Class)
	{
		ISame_DOTA_TemplateInterface* Interface = Cast< ISame_DOTA_TemplateInterface>(GetOwningActorFromActorInfo());

		FVector SocketLocation = Interface->GetSocketLocation(SpawnActorSocketName);
		FRotator SpawnRotator;
		
		FRotator SlefToTagerRotator = UKismetMathLibrary::FindLookAtRotation(GetAvatarActorFromActorInfo()->GetActorLocation(), TargetActor->GetActorLocation());
		SpawnRotator = FRotator(0.f, SlefToTagerRotator.Yaw, 0.f);
		
		TargetActor->GetActorLocation();

		ASame_DOTA_MeleeProjectile* Projectile = GetWorld()->SpawnActor<ASame_DOTA_MeleeProjectile>(
			Projectile_Class,
			SocketLocation,
			SpawnRotator
		);

		float Damage = OwnerActor->GetAttributeSet()->GetAttack();

		Projectile->SetOwnerActorTagetActorAndDamageType(OwnerActor, TargetActor, AblityType_DamageType, Damage);
	}
}


