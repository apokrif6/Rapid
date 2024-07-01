// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ReloadAbility.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/Attributes/RangeAttributeSet.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UReloadAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo,
                                     const FGameplayEventData* TriggerEventData)
{
	if (const USkeletalMeshComponent* AvatarSkeletalMeshComponent = ActorInfo->SkeletalMeshComponent.Get();
		!AvatarSkeletalMeshComponent)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}

	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	StreamableManager.RequestAsyncLoad(AnimMontage.ToSoftObjectPath(), [this, TriggerEventData]
	{
		PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this, FName("ReloadAbility"), AnimMontage.Get(), 1);
		PlayMontageAndWait->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelled);
		PlayMontageAndWait->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelled);
		PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCompleted);
		PlayMontageAndWait->ReadyForActivation();

		Super::ActivateAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, TriggerEventData);
	});
}

void UReloadAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UReloadAbility::OnMontageCancelled()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UReloadAbility::OnMontageCompleted()
{
	UGameplayEffect* GameplayEffect = NewObject<UGameplayEffect>(this);
	FGameplayModifierInfo GameplayModifierInfo;
	GameplayModifierInfo.Attribute = URangeAttributeSet::GetAmmoAttribute();
	GameplayModifierInfo.ModifierOp = EGameplayModOp::Override;
	GameplayModifierInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude{
		FScalableFloat(
			GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(URangeAttributeSet::GetMaxAmmoAttribute()))
	};
	GameplayEffect->Modifiers.Add(GameplayModifierInfo);

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectToSelf(
		GameplayEffect, 1, FGameplayEffectContextHandle());

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
