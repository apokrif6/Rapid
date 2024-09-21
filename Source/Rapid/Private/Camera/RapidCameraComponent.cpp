// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/RapidCameraComponent.h"

FCameraModeView::FCameraModeView()
{
}

void FCameraModeView::Blend(const FCameraModeView& Other, const float OtherWeight)
{
	if (OtherWeight <= 0.0f)
	{
		return;
	}

	if (OtherWeight >= 1.0f)
	{
		*this = Other;
		return;
	}

	Location = FMath::Lerp(Location, Other.Location, OtherWeight);

	const FRotator DeltaRotation = (Other.Rotation - Rotation).GetNormalized();
	Rotation = Rotation + OtherWeight * DeltaRotation;

	const FRotator DeltaControlRotation = (Other.ControlRotation - ControlRotation).GetNormalized();
	ControlRotation = ControlRotation + OtherWeight * DeltaControlRotation;

	FOV = FMath::Lerp(FOV, Other.FOV, OtherWeight);
}

void URapidCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	//TODO
	//process camera modifiers

	FCameraModeView CameraModeView;

	SetWorldLocationAndRotation(CameraModeView.Location, CameraModeView.Rotation);

	DesiredView.Location = CameraModeView.Location;
	DesiredView.Rotation = CameraModeView.Rotation;
	DesiredView.FOV = CameraModeView.FOV;

	Super::GetCameraView(DeltaTime, DesiredView);
}

void URapidCameraComponent::SetCameraMode(const TSubclassOf<URapidCameraMode>& CameraMode,
                                          FGameplayAbilitySpecHandle SpecHandle)
{
	CurrentCameraMode = GetCameraModeInstance(CameraMode);
}

URapidCameraMode* URapidCameraComponent::GetCameraModeInstance(const TSubclassOf<URapidCameraMode>& CameraModeClass)
{
	for (URapidCameraMode* CameraMode : CameraModeInstances)
	{
		if (CameraMode && CameraMode->GetClass() == CameraModeClass)
		{
			return CameraMode;
		}
	}

	URapidCameraMode* NewCameraMode = NewObject<URapidCameraMode>(GetOuter(), CameraModeClass, NAME_None, RF_NoFlags);
	check(NewCameraMode);

	CameraModeInstances.Add(NewCameraMode);

	return NewCameraMode;
}
