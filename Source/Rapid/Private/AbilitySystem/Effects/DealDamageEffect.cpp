// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/DealDamageEffect.h"
#include "AbilitySystem/Calculations/DamageExecutionCalculation.h"

UDealDamageEffect::UDealDamageEffect()
{
	FGameplayEffectExecutionDefinition GameplayEffectExecutionDefinition;
	GameplayEffectExecutionDefinition.CalculationClass = UDamageExecutionCalculation::StaticClass();
	Executions.Add(GameplayEffectExecutionDefinition);
}
