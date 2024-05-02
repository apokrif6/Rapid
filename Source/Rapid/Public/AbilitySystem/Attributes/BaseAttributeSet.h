// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class RAPID_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Damage)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
