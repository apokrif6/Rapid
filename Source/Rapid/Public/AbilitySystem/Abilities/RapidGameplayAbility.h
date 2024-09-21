// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RapidGameplayAbility.generated.h"

class URapidCameraMode;

/**
 * Base class with common logic for every ability
 */
UCLASS()
class RAPID_API URapidGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SetCameraMode(TSubclassOf<URapidCameraMode> CameraMode);
};
