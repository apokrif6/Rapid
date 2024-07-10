// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Common/HitReactionAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Kismet/KismetMathLibrary.h"

static int32 GDisplayHitReactionDebug = 0;
static FAutoConsoleVariableRef CVarHitReactionDebug(
	TEXT("Rapid.DisplayHitReactionDebug"),
	GDisplayHitReactionDebug,
	TEXT("Display debug visualizers for hit reactions (0 - disabled. 1 - enabled)"),
	ECVF_Cheat);

void UHitReactionAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	if (const USkeletalMeshComponent* AvatarSkeletalMeshComponent = ActorInfo->SkeletalMeshComponent.Get();
		!AvatarSkeletalMeshComponent)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	if (const UHitNormalPayloadData* HitNormalData = Cast<UHitNormalPayloadData>(TriggerEventData->OptionalObject))
	{
		const EHitReactionSide HitReactionSide = FindHitReactionDirection(HitNormalData->ActorHitFromLocation);

		if (UAnimMontage* HitReactionAnimMontage = FindHitReactionMontage(HitReactionSide))
		{
			PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
				this, FName("HitReactionAbility"), HitReactionAnimMontage, 1);
			PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
			PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelled);
			PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);
			PlayMontageAndWait->ReadyForActivation();

			Super::ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);
		}

		//TODO
		//remove after adding data asset with montages!!
		//it's here only for testing purpose
		Super::ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);
	}
}

void UHitReactionAbility::OnMontageCancelled()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UHitReactionAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

EHitReactionSide UHitReactionAbility::FindHitReactionDirection(const FVector& ImpactPoint) const
{
	const FVector ActorLocation = GetActorInfo().AvatarActor.Get()->GetActorLocation();

	float DotProduct = FVector::DotProduct(ActorLocation, ImpactPoint.GetSafeNormal());

	float Degree = UKismetMathLibrary::DegAcos(DotProduct);

	if (CVarHitReactionDebug->GetInt() > 0)
	{
		DrawDebugSphere(GetActorInfo().AvatarActor.Get()->GetWorld(), ImpactPoint, 15.f, 32, FColor::Red, false,
		                1.f, 0, 3);

		DrawDebugLine(GetActorInfo().AvatarActor.Get()->GetWorld(), ActorLocation,
		              (ImpactPoint - ActorLocation) * 300.f, FColor::Yellow, false,
		              1.f, 0, 5);
	}

	return EHitReactionSide::None;
}

UAnimMontage* UHitReactionAbility::FindHitReactionMontage(const EHitReactionSide HitReactionSide)
{
	return nullptr;
}
