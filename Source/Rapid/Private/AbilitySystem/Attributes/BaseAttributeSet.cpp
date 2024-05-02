// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/BaseAttributeSet.h"

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, 100);
	}

	if (Attribute == GetDamageAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, 100);
	}
}
