// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ActivateAbilityAndWaitAction.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
struct FGameplayTag;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActivateAndWaitAbilityActionEvent);

/**
 * 
 */
UCLASS()
class RAPID_API UActivateAbilityAndWaitAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FActivateAndWaitAbilityActionEvent OnStarted;

	UPROPERTY(BlueprintAssignable)
	FActivateAndWaitAbilityActionEvent OnEnded;

	UPROPERTY(BlueprintAssignable)
	FActivateAndWaitAbilityActionEvent OnFailed;

	UFUNCTION(BlueprintCallable, DisplayName="Activate Ability And Wait Action",
		meta=(WorldContext="WorldContext", BlueprintInternalUseOnly="true"))
	static UActivateAbilityAndWaitAction* ActivateAbilityAndWaitAction(const UObject* WorldContext,
	                                                                   UPARAM(ref) UAbilitySystemComponent*
	                                                                   InAbilityComponent,
	                                                                   const FGameplayTag AbilityTag);

	virtual void Activate() override;

private:
	TWeakObjectPtr<UWorld> ContextWorld = nullptr;

	TWeakObjectPtr<UAbilitySystemComponent> AbilityComponent = nullptr;

	TWeakObjectPtr<UGameplayAbility> GameplayAbility = nullptr;

	FDelegateHandle BoundOnGameplayAbilityEndedDelegateHandle;

	void WaitForAbilityEnd(UGameplayAbility* EndedGameplayAbility);
};
