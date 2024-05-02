// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Calculations/DamageExecutionCalculation.h"
#include "AbilitySystem/Attributes/BaseAttributeSet.h"
#include "AbilitySystem/Contexts/DealDamageEffectContext.h"

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Damage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Health, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics StaticDamageStatics;
	return StaticDamageStatics;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
}

void UDamageExecutionCalculation::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.TargetTags = TargetTags;
	EvaluateParameters.SourceTags = SourceTags;

	int32 BaseDamage = 0;
	float RandomDamageMultiplier = 1.f;
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	if (const FDealDamageEffectContext* ContextHandle = static_cast<FDealDamageEffectContext*>(Spec.GetContext().Get()))
	{
		BaseDamage = ContextHandle->BaseDamage;
		RandomDamageMultiplier = ContextHandle->RandomDamageMultiplier;
	}

	//TODO
	//add buffs/debuffs calculation
	const int32 CalculatedDamage = FMath::RandRange(BaseDamage, static_cast<int>(BaseDamage * RandomDamageMultiplier));
	const int32 FinalDamage = FMath::Clamp<int32>(CalculatedDamage, 0, CalculatedDamage);

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(DamageStatics().HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}
