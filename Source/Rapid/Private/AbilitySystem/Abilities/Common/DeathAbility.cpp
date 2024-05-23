// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Common/DeathAbility.h"
#include "GameFramework/MovementComponent.h"

void UDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                    const FGameplayEventData* TriggerEventData)
{
	if (USkeletalMeshComponent* AvatarSkeletalMeshComponent = ActorInfo->SkeletalMeshComponent.Get())
	{
		AvatarSkeletalMeshComponent->SetCollisionProfileName(RagdollProfileName);
		AvatarSkeletalMeshComponent->SetSimulatePhysics(true);
	}

	if (UMovementComponent* AvatarMovementComponent = ActorInfo->MovementComponent.Get())
	{
		AvatarMovementComponent->StopMovementImmediately();
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
