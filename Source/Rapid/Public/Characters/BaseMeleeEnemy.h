// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseMeleeEnemy.generated.h"

class UMeleeWeaponTraceComponent;

UCLASS()
class RAPID_API ABaseMeleeEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseMeleeEnemy();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMeleeWeaponTraceComponent> MeleeWeaponTraceComponent;
};
