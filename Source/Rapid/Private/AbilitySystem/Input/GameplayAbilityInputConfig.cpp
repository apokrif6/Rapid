// Fill out your copyright notice in the Description page of Project Settings.


#include "Rapid/Public/AbilitySystem/Input/GameplayAbilityInputConfig.h"

#if WITH_EDITOR
void UGameplayAbilityInputConfig::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (const FProperty* Property = PropertyChangedEvent.Property;
		Property && Property->GetFName() == GET_MEMBER_NAME_CHECKED(UGameplayAbilityInputConfig, InputAbilities)
		&& !InputAbilities.IsEmpty())
	{
		TArray<FGameplayInputAbilityInfo> InputAbilitiesArray = InputAbilities.Array();
		InputAbilities.Reset();

		for (int32 i = 0; i < InputAbilitiesArray.Num(); ++i)
		{
			FGameplayInputAbilityInfo& Info = InputAbilitiesArray[i];
			Info.InputID = i;
			InputAbilities.Add(Info);
		}
	}
}
#endif
