// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/ActivateAbilityAndWaitAction.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"

UActivateAbilityAndWaitAction* UActivateAbilityAndWaitAction::ActivateAbilityAndWaitAction(const UObject* WorldContext,
	UAbilitySystemComponent* InAbilityComponent, const FGameplayTag AbilityTag)
{
	UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("WorldContext is not valid!")))
	{
		return nullptr;
	}

	if (!ensureAlwaysMsgf(IsValid(InAbilityComponent), TEXT("AbilityComponent is not valid!")))
	{
		return nullptr;
	}

	if (!ensureAlwaysMsgf(!AbilityTag.MatchesTag(AbilityTag.EmptyTag), TEXT("AbilityTag is empty!")))
	{
		return nullptr;
	}
	const FGameplayTagContainer AbilityTagContainer = FGameplayTagContainer(AbilityTag);

	TArray<FGameplayAbilitySpecHandle> GameplayAbilitySpecHandles;
	InAbilityComponent->FindAllAbilitiesWithTags(GameplayAbilitySpecHandles, AbilityTagContainer);

	if (!ensureAlwaysMsgf(!GameplayAbilitySpecHandles.IsEmpty(),
	                      TEXT("GameplayAbilitySpecHandles is empty. Can't find abilities associated with tag!")))
	{
		return nullptr;
	}

	UGameplayAbility* FoundAbility = InAbilityComponent->FindAbilitySpecFromHandle(GameplayAbilitySpecHandles[0])->
	                                                     Ability;
	if (!ensureAlwaysMsgf(IsValid(FoundAbility), TEXT("FoundAbility is not valid!")))
	{
		return nullptr;
	}

	UActivateAbilityAndWaitAction* NewAction = NewObject<UActivateAbilityAndWaitAction>();
	NewAction->ContextWorld = ContextWorld;
	NewAction->AbilityComponent = InAbilityComponent;
	NewAction->GameplayAbility = FoundAbility;
	NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
	return NewAction;
}

void UActivateAbilityAndWaitAction::Activate()
{
	for (const FGameplayAbilitySpec& GameplayAbilitySpec : AbilityComponent->GetActivatableAbilities())
	{
		if (GameplayAbilitySpec.Ability == GameplayAbility)
		{
			if (AbilityComponent->TryActivateAbility(GameplayAbilitySpec.Handle))
			{
				OnStarted.Broadcast();

				BoundOnGameplayAbilityEndedDelegateHandle = AbilityComponent->AbilityEndedCallbacks.AddUObject(
					this, &ThisClass::WaitForAbilityEnd);

				return;
			}

			OnFailed.Broadcast();
		}
	}

	OnFailed.Broadcast();
}

void UActivateAbilityAndWaitAction::WaitForAbilityEnd(UGameplayAbility* EndedGameplayAbility)
{
	if (GameplayAbility == EndedGameplayAbility->GetClass()->GetDefaultObject())
	{
		OnEnded.Broadcast();

		AbilityComponent->AbilityEndedCallbacks.Remove(BoundOnGameplayAbilityEndedDelegateHandle);
	}
}
