// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "AbilitySystem/Attributes/RangeAttributeSet.h"

void UHUDWidget::NativeConstruct()
{
	if (const APawn* OwningPawn = GetOwningPlayerPawn())
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = OwningPawn->GetComponentByClass<
			UAbilitySystemComponent>())
		{
			OnHealthChanged(AbilitySystemComponent->GetNumericAttribute(UBaseAttributeSet::GetHealthAttribute()));

			OnAmmoChanged(AbilitySystemComponent->GetNumericAttribute(URangeAttributeSet::GetAmmoAttribute()));

			OnHealthAttributeChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				                                                         UBaseAttributeSet::GetHealthAttribute()).
			                                                         AddUObject(this, &ThisClass::OnAttributeChanged);

			OnAmmoAttributeChangedHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				                                                       URangeAttributeSet::GetAmmoAttribute()).
			                                                       AddUObject(this, &ThisClass::OnAttributeChanged);
		}
	}

	Super::NativeConstruct();
}

void UHUDWidget::NativeDestruct()
{
	if (const APawn* OwningPawn = GetOwningPlayerPawn())
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = OwningPawn->GetComponentByClass<
			UAbilitySystemComponent>())
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHealthAttribute()).
			                        Remove(OnHealthAttributeChangedHandle);

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(URangeAttributeSet::GetAmmoAttribute()).
			                        Remove(OnAmmoAttributeChangedHandle);
		}
	}

	Super::NativeDestruct();
}

void UHUDWidget::OnAttributeChanged(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.Attribute == UBaseAttributeSet::GetHealthAttribute())
		OnHealthChanged(ChangeData.NewValue);

	if (ChangeData.Attribute == URangeAttributeSet::GetAmmoAttribute())
		OnAmmoChanged(ChangeData.NewValue);
}
