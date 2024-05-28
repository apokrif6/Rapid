// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"


UCLASS(ClassGroup=("AI"), meta=(BlueprintSpawnableComponent))
class RAPID_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPatrolComponent();

	UFUNCTION(BlueprintCallable)
	void SetPointToNext();

	UFUNCTION(BlueprintCallable)
	FVector GetCurrentPointLocation() const;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Config")
	TArray<TObjectPtr<AActor>> Points;

private:
	TObjectPtr<AActor> GetCurrentPoint() const;

	int32 CurrentPointIndex = 0;
};
