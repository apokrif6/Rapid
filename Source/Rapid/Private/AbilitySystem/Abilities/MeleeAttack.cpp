﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MeleeAttack.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/Contexts/DealDamageEffectContext.h"
#include "AbilitySystem/Effects/DealDamageEffect.h"
#include "Kismet/KismetSystemLibrary.h"

void UMeleeAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo,
                                   const FGameplayEventData* TriggerEventData)
{
	if (const USkeletalMeshComponent* AvatarSkeletalMeshComponent = ActorInfo->SkeletalMeshComponent.Get();
		!AvatarSkeletalMeshComponent)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, FName("AttackAbility"), AnimMontage.Get(), 1);
	PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
	PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelled);
	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);
	PlayMontageAndWait->ReadyForActivation();

	FHitResult HitResult;

	TArray ActorsToIgnore{ActorInfo->AvatarActor.Get()};

	//TODO
	//consider creating trace component for dealing damage
	
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(), ActorInfo->AvatarActor->GetActorLocation(), ActorInfo->AvatarActor->GetActorLocation(),
		AttackRadius, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, HitResult, true);

	Super::ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);

	if (bHit)
	{
		UAbilitySystemComponent* HitAbilitySystemComponent = HitResult.GetActor()->GetComponentByClass<
			UAbilitySystemComponent>();
		if (!HitAbilitySystemComponent) return;

		UDealDamageEffect* GameplayEffect = NewObject<UDealDamageEffect>(this);
		FDealDamageEffectContext* DealDamageEffectContext = new FDealDamageEffectContext;
		DealDamageEffectContext->BaseDamage = Damage;
		FGameplayEffectContextHandle GameplayEffectContextHandle{DealDamageEffectContext};

		HitAbilitySystemComponent->ApplyGameplayEffectToSelf(GameplayEffect, 1, GameplayEffectContextHandle);
	}
}

void UMeleeAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                              bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMeleeAttack::OnMontageCancelled()
{
}

void UMeleeAttack::OnMontageCompleted()
{
}