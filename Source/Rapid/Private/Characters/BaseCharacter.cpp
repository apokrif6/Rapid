// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "AbilitySystem/Attributes/BaseAttributeSet.h"
#include "AbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		BaseAttributeSet = AbilitySystemComponent->GetSet<UBaseAttributeSet>();
	}
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	SetOwner(NewController);
}
