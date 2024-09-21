// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RapidGameplayAbility.h"
#include "Camera/RapidCameraComponent.h"

void URapidGameplayAbility::SetCameraMode(TSubclassOf<URapidCameraMode> CameraMode)
{
	if (CurrentActorInfo || CurrentActorInfo->AvatarActor.Get())
		return;

	if (URapidCameraComponent* CameraComponent = CurrentActorInfo->AvatarActor.Get()->GetComponentByClass<
		URapidCameraComponent>())
	{
		CameraComponent->SetCameraMode(CameraMode, CurrentSpecHandle);
	}
}
