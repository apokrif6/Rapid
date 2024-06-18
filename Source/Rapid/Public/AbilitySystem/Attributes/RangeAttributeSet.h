// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "RangeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RAPID_API URangeAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(URangeAttributeSet, Ammo)
};
