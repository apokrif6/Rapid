// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/Components/MeleeWeaponTraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Logs/RapidLog.h"

UMeleeWeaponTraceComponent::UMeleeWeaponTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMeleeWeaponTraceComponent::EnableCollision()
{
	ClearHitActors();

	bIsEnabled = true;
}

void UMeleeWeaponTraceComponent::DisableCollision()
{
	bIsEnabled = false;
}

void UMeleeWeaponTraceComponent::CollisionTrace()
{
	if (!CollisionMeshComponent)
	{
		UE_LOG(RapidCombatLog, Warning, TEXT("Can't find MeshComponent for MeleeWeaponTraceComponent. Owner : %s"),
		       *GetOwner()->GetName())
	}

	const FVector StartLocation = CollisionMeshComponent->GetSocketLocation(StartSocketName);
	const FVector EndLocation = CollisionMeshComponent->GetSocketLocation(EndSocketName);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<FHitResult> HitResults;

	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), StartLocation, EndLocation, Radius, ObjectTypes, false,
	                                                 ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);

	for (FHitResult HitResult : HitResults)
	{
		LastHitResult = HitResult;

		if (AlreadyHitActors.Contains(HitResult.GetActor()))
			continue;

		AlreadyHitActors.Add(HitResult.GetActor());

		//OnActorHit.Broadcast(HitResult);
	}
}

void UMeleeWeaponTraceComponent::ClearHitActors()
{
	AlreadyHitActors.Empty();
}

void UMeleeWeaponTraceComponent::SetCollisionMeshComponent(UPrimitiveComponent* PrimitiveComponent)
{
}

void UMeleeWeaponTraceComponent::AddActorToIgnore(AActor* Actor)
{
	ActorsToIgnore.AddUnique(Actor);
}

void UMeleeWeaponTraceComponent::RemoveActorToIgnore(AActor* Actor)
{
	ActorsToIgnore.Remove(Actor);
}

void UMeleeWeaponTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		AddActorToIgnore(Owner);

		CollisionMeshComponent = Owner->GetComponentByClass<USkeletalMeshComponent>();
	}
}

void UMeleeWeaponTraceComponent::TickComponent(float DeltaTime)
{
}
