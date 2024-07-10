// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "HitReactionAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;

UCLASS(Blueprintable)
class RAPID_API UHitNormalPayloadData : public UObject
{
	GENERATED_BODY()

public:
	FVector ImpactPoint;
};

UENUM()
enum class EHitReactionSide : uint8
{
	None UMETA(Hidden),
	Front,
	Back,
	Left,
	Right
};

UCLASS()
class RAPID_API UHitReactionAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait;

	UFUNCTION()
	void OnMontageCancelled();

	UFUNCTION()
	void OnMontageCompleted();

	EHitReactionSide FindHitReactionDirection(const FVector& ImpactPoint) const;

	UAnimMontage* FindHitReactionMontage(const EHitReactionSide HitReactionSide);
};
