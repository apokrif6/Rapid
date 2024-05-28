// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Components/PatrolComponent.h"

UPatrolComponent::UPatrolComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPatrolComponent::SetPointToNext()
{
	CurrentPointIndex = (CurrentPointIndex + 1) % Points.Num();
}

FVector UPatrolComponent::GetCurrentPointLocation() const
{
	if (const TObjectPtr<AActor> CurrentPointActor = GetCurrentPoint())
	{
		return CurrentPointActor->GetActorLocation();
	}

	return FVector{};
}

TObjectPtr<AActor> UPatrolComponent::GetCurrentPoint() const
{
	return Points.IsValidIndex(CurrentPointIndex) ? Points[CurrentPointIndex] : nullptr;
}
