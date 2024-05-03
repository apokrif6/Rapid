// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeleeWeaponTraceComponent.generated.h"


UCLASS(ClassGroup="Combat", meta=(BlueprintSpawnableComponent))
class RAPID_API UMeleeWeaponTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMeleeWeaponTraceComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	FName StartSocketName = FName("WeaponStartSocket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	FName EndSocketName = FName("WeaponEndSocket");

	void EnableCollision();

	void DisableCollision();

	void CollisionTrace();

	void ClearHitActors();

	TObjectPtr<UPrimitiveComponent> GetCollisionMeshComponent() const { return CollisionMeshComponent; }

	TArray<AActor*> GetAlreadyHitActors() const { return AlreadyHitActors; }

	bool IsEnabled() const { return bIsEnabled; }

	FHitResult GetLastHitResult() const { return LastHitResult; }

	void AddActorToIgnore(AActor* Actor);

	void RemoveActorToIgnore(AActor* Actor);

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> CollisionMeshComponent = nullptr;

	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;

	bool bIsEnabled = false;

	FHitResult LastHitResult;

	float Radius = 25.f;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
};
