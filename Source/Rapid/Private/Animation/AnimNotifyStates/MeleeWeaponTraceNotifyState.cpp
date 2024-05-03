// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyStates/MeleeWeaponTraceNotifyState.h"
#include "Combat/Components/MeleeWeaponTraceComponent.h"

void UMeleeWeaponTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration,
                                               const FAnimNotifyEventReference& EventReference)
{
	UMeleeWeaponTraceComponent* MeleeWeaponTraceComponent = MeshComp->GetOwner()->GetComponentByClass<
		UMeleeWeaponTraceComponent>();
	if (!MeleeWeaponTraceComponent) return;

	MeleeWeaponTraceComponent->EnableCollision();
}

void UMeleeWeaponTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp,
                                             UAnimSequenceBase* Animation,
                                             const FAnimNotifyEventReference& EventReference)
{
	UMeleeWeaponTraceComponent* MeleeWeaponTraceComponent = MeshComp->GetOwner()->GetComponentByClass<
		UMeleeWeaponTraceComponent>();
	if (!MeleeWeaponTraceComponent) return;

	MeleeWeaponTraceComponent->DisableCollision();
}
