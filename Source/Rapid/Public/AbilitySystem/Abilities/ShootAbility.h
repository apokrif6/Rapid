// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShootAbility.generated.h"

class UAbilityTask_PlayMontageAndWait;
/**
 * 
 */
UCLASS()
class RAPID_API UShootAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	TSoftObjectPtr<UAnimMontage> ShootAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta=(UIMin = 1))
	int32 Damage = 10;

	//TODO
	//should be replaced with struct
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta=(UIMin = 1))
	float RandomDamageMultiplier = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta=(UIMin = 1))
	int32 ShotDistance = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta=(UIMin = 1))
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	FName MuzzleSocket;

private:
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait;

	UFUNCTION()
	void OnMontageCancelled();

	UFUNCTION()
	void OnMontageCompleted();
};
