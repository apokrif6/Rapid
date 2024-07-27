// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Common/HitReactionAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/KismetMathLibrary.h"

static int32 GDisplayHitReactionDebug = 0;
static TAutoConsoleVariable CVarHitReactionDebug(
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
		return;
	}

	if (const UHitNormalPayloadData* HitNormalData = Cast<UHitNormalPayloadData>(TriggerEventData->OptionalObject))
	{
		const EHitReactionSide HitReactionSide = FindHitReactionDirection(HitNormalData->ImpactPoint);

		TSoftObjectPtr<UAnimMontage>* HitReactionMontage = HitReactionMontages.Find(HitReactionSide);
		if (!HitReactionMontage || HitReactionMontage->IsNull())
		{
			CancelAbility(Handle, ActorInfo, ActivationInfo, true);
			return;
		}

		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		StreamableManager.RequestAsyncLoad(HitReactionMontage->ToSoftObjectPath(),
		                                   [this, HitReactionMontage, TriggerEventData]
		                                   {
			                                   PlayMontageAndWait =
				                                   UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
					                                   this, FName("HitReactionAbility"), HitReactionMontage->Get(), 1);
			                                   PlayMontageAndWait->OnCancelled.AddDynamic(
				                                   this, &ThisClass::OnMontageCancelled);
			                                   PlayMontageAndWait->OnInterrupted.AddDynamic(
				                                   this, &ThisClass::OnMontageCancelled);
			                                   PlayMontageAndWait->OnCompleted.AddDynamic(
				                                   this, &ThisClass::OnMontageCompleted);
			                                   PlayMontageAndWait->ReadyForActivation();

			                                   Super::ActivateAbility(CurrentSpecHandle, CurrentActorInfo,
			                                                          CurrentActivationInfo, TriggerEventData);
		                                   });
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
	EHitReactionSide HitReactionSide;

	const FVector ActorLocation = GetActorInfo().AvatarActor.Get()->GetActorLocation();

	const FVector NormalizedDirection = (ImpactPoint - ActorLocation).GetSafeNormal();

	const float DotForward = FVector::DotProduct(NormalizedDirection,
	                                             GetActorInfo().AvatarActor.Get()->GetActorForwardVector());

	const float DotRight = FVector::DotProduct(NormalizedDirection,
	                                           GetActorInfo().AvatarActor.Get()->GetActorRightVector());

	if (FMath::Abs(DotForward) >= FMath::Abs(DotRight))
	{
		if (DotForward > 0)
		{
			HitReactionSide = EHitReactionSide::Front;
		}
		else
		{
			HitReactionSide = EHitReactionSide::Back;
		}
	}
	else
	{
		if (DotRight > 0)
		{
			HitReactionSide = EHitReactionSide::Right;
		}
		else
		{
			HitReactionSide = EHitReactionSide::Left;
		}
	}

	//Consider creating new Debugger Category for this
#if WITH_EDITOR
	if (CVarHitReactionDebug.GetValueOnGameThread() > 0)
	{
		DrawDebugSphere(GetActorInfo().AvatarActor.Get()->GetWorld(), ImpactPoint, 15.f, 32, FColor::Red, false,
		                1.f, 0, 3);

		DrawDebugLine(GetActorInfo().AvatarActor.Get()->GetWorld(), ActorLocation,
		              (ImpactPoint - ActorLocation) * 300.f, FColor::Yellow, false,
		              1.f, 0, 5);

		const FString HitReactionSideString = StaticEnum<EHitReactionSide>()->GetAuthoredNameStringByValue(
			static_cast<int64>(HitReactionSide));
		DrawDebugString(GetActorInfo().AvatarActor.Get()->GetWorld(), ActorLocation,
		                TEXT("Actor was hit from " + HitReactionSideString), nullptr, FColor::Red, 1.f);
	}
#endif

	return HitReactionSide;
}
