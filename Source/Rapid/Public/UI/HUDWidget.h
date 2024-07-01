// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/RangeAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UAbilityAsync_WaitAttributeChanged;
/**
 * 
 */
UCLASS()
class RAPID_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void OnAttributeChanged(const FOnAttributeChangeData& ChangeData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(const float NewHealth);

	UFUNCTION(BlueprintImplementableEvent)
	void OnAmmoChanged(const float NewAmmo);

private:
	FDelegateHandle OnHealthAttributeChangedHandle;

	FDelegateHandle OnAmmoAttributeChangedHandle;
};
