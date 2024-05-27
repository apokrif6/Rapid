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

	UFUNCTION(BlueprintPure)
	void SetPointToNext();

	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<USceneComponent> GetCurrentPoint() const;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Config")
	TArray<TSoftObjectPtr<USceneComponent>> Points;

private:
	int32 CurrentPointIndex = INDEX_NONE;
};
