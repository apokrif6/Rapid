// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ShootAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/Abilities/Common/HitReactionAbility.h"
#include "AbilitySystem/Contexts/DealDamageEffectContext.h"
#include "AbilitySystem/Effects/DealDamageEffect.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/KismetSystemLibrary.h"

void UShootAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                    const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (const USkeletalMeshComponent* AvatarSkeletalMeshComponent = ActorInfo->SkeletalMeshComponent.Get();
		!AvatarSkeletalMeshComponent)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(ShootAnimMontage.ToSoftObjectPath(), [this, TriggerEventData, ActorInfo]
	{
		PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, FName("AttackAbility"), ShootAnimMontage.Get(), 1);
		PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
		PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelled);
		PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);

		PlayMontageAndWait->ReadyForActivation();

		FVector CameraViewLocation;
		FRotator CameraViewRotation;
		const AController* AvatarController = ActorInfo->AvatarActor->GetInstigatorController();
		AvatarController->GetPlayerViewPoint(CameraViewLocation, CameraViewRotation);

		const FVector TraceStart = CameraViewLocation;
		//TODO
		//add spread based on speed
		const float HalfRadius = FMath::DegreesToRadians(BulletSpread);
		const FVector ShotDirection = FMath::VRandCone(CameraViewRotation.Vector(), HalfRadius);
		const FVector TraceEnd = TraceStart + ShotDirection * ShotDistance;

		FHitResult HitResult;

		TArray ActorsToIgnore{ActorInfo->AvatarActor.Get()};

		bool bHit = UKismetSystemLibrary::LineTraceSingle(
			GetWorld(), ActorInfo->SkeletalMeshComponent->GetSocketLocation(MuzzleSocket),
			TraceEnd, UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false, ActorsToIgnore,
			EDrawDebugTrace::ForDuration, HitResult, true);

		Super::ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);

		if (bHit && HitResult.GetActor())
		{
			UAbilitySystemComponent* HitAbilitySystemComponent = HitResult.GetActor()->GetComponentByClass<
				UAbilitySystemComponent>();
			if (!HitAbilitySystemComponent) return;

			UDealDamageEffect* GameplayEffect = NewObject<UDealDamageEffect>(this);
			FDealDamageEffectContext* DealDamageEffectContext = new FDealDamageEffectContext;
			DealDamageEffectContext->BaseDamage = Damage;
			DealDamageEffectContext->RandomDamageMultiplier = RandomDamageMultiplier;
			FGameplayEffectContextHandle GameplayEffectContextHandle{DealDamageEffectContext};

			HitAbilitySystemComponent->ApplyGameplayEffectToSelf(GameplayEffect, 1, GameplayEffectContextHandle);

			//TODO
			//move to better place
			FGameplayEventData EventData;
			UHitNormalPayloadData* HitNormalPayloadData = NewObject<UHitNormalPayloadData>();
			HitNormalPayloadData->ImpactPoint = HitResult.ImpactPoint;
			EventData.OptionalObject = HitNormalPayloadData;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitResult.GetActor(), HitReactionGameplayTag,
			                                                         EventData);
		}
	});
}

void UShootAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                               bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UShootAbility::OnMontageCancelled()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UShootAbility::OnMontageCompleted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
