// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RapidCameraMode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class RAPID_API URapidCameraMode : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera",
		Meta = (UIMin = "5.0", UIMax = "170", ClampMin = "5.0", ClampMax = "170.0"))
	float FieldOfView;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	TObjectPtr<const UCurveFloat> TargetOffsetCurve;
};
