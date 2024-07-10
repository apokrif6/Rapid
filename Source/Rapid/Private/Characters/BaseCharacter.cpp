// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "AbilitySystem/Attributes/BaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Abilities/Common/HitReactionAbility.h"
#include "AbilitySystem/Input/GameplayAbilityInputConfig.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeGameplayAbilitySystem();
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

void ABaseCharacter::InitializeGameplayAbilitySystem() const
{
	if (!GameplayAbilityInputConfig)
		return;

	for (const FGameplayInputAbilityInfo& InputAbility : GameplayAbilityInputConfig->GetInputAbilities())
	{
		if (InputAbility.IsValid())
		{
			const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(
				InputAbility.GameplayAbilityClass.LoadSynchronous(), 1 /* default ability level */,
				InputAbility.InputID);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}
