// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIBaseController.generated.h"

UCLASS()
class RAPID_API AAIBaseController : public AAIController
{
	GENERATED_BODY()

public:
	AAIBaseController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	FName TargetActorBlackboardKey = FName("TargetActor");

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
};
