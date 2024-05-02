// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBaseAttributeSet;

UCLASS()
class RAPID_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	const UBaseAttributeSet* BaseAttributeSet;

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
};
