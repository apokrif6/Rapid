// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UObject/Object.h"
#include "DealDamageEffectContext.generated.h"

/**
 * 
 */
USTRUCT()
struct RAPID_API FDealDamageEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

	int32 BaseDamage = 0;

	float RandomDamageMultiplier = 1.f;

	virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }
};
