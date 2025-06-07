// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetActor/Same_DOTA_TargetActor.h"




void ASame_DOTA_TargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	
	PrimaryPC = Cast<APlayerController>(Ability);//->GetOwningActorFromActorInfo()->GetInstigatorController()

}

void ASame_DOTA_TargetActor::ConfirmTargetingAndContinue()
{
	/*FVector MousePoint;
	GetMouseLocation(MousePoint);

	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	bool QueryResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		MousePoint,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(SelectedRadius),
		QueryParams
	);*/

	/*if (QueryResult)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			APawn* Enemy = Cast<APawn>(OverlapResults[i].GetActor());
			if (Enemy && !OverlapActors.Contains(Enemy))
			{
				OverlapActors.Add(Enemy);
			}
		}		
	}*/
	

	////包装发送
	//FGameplayAbilityTargetDataHandle TargetDataHandle;
	//FGameplayAbilityTargetData_LocationInfo* CenterLoc = new FGameplayAbilityTargetData_LocationInfo();
	//CenterLoc->TargetLocation.LiteralTransform = FTransform(MousePoint);
	//CenterLoc->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	////0号负载
	//TargetDataHandle.Add(CenterLoc);

	//if (!OverlapActors.IsEmpty())
	//{
	//	FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
	//	//1号负载
	//	ActorArray->SetActors(OverlapActors);
	//}


}

bool ASame_DOTA_TargetActor::GetMouseLocation(FVector& InMousePoint)
{
	FVector ViewLoc;
	FRotator ViewRot;
	PrimaryPC->GetPlayerViewPoint(ViewLoc, ViewRot);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	bool TraceResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		ViewLoc,
		ViewLoc+ViewRot.Vector()*5000.f,
		ECollisionChannel::ECC_Visibility,
		QueryParams
	);

	if (TraceResult)
	{
		InMousePoint = HitResult.ImpactPoint;
	}
	
	return TraceResult;
}
