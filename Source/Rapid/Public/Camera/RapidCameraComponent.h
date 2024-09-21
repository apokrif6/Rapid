// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RapidCameraMode.h"
#include "AbilitySystem/Abilities/RapidGameplayAbility.h"
#include "Camera/CameraComponent.h"

#include

#include "RapidCameraComponent.generated.h"

USTRUCT(BlueprintType)
struct FAbilityCameraModifiers
{
	GENERATED_BODY()

	FAbilityCameraModifiers();

	//TODO
	//create In and Out blend modifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraLengthOffset = 55.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlendTime = 0.25f;
};

struct FCameraModeView
{
	FCameraModeView();

	void Blend(const FCameraModeView& Other, float OtherWeight);

	FVector Location;

	FRotator Rotation;

	FRotator ControlRotation;

	float FOV = ForceInit;
};

/**
 * Component to handle camera logic and blends
 */
UCLASS()
class RAPID_API URapidCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

	void SetCameraMode(const TSubclassOf<URapidCameraMode>& CameraMode, FGameplayAbilitySpecHandle SpecHandle);

private:
	URapidCameraMode* GetCameraModeInstance(const TSubclassOf<URapidCameraMode>& CameraModeClass);

	UPROPERTY()
	URapidCameraMode* CurrentCameraMode;

	UPROPERTY()
	TArray<TObjectPtr<URapidCameraMode>> CameraModeInstances;
};
