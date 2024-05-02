// Rapid

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayAbilityInputConfig.generated.h"

class UInputAction;
class UGameplayAbility;


USTRUCT()
struct FGameplayInputAbilityInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TSoftClassPtr<UGameplayAbility> GameplayAbilityClass;

	UPROPERTY(EditAnywhere, Category = "GameplayInputAbilityInfo")
	TSoftObjectPtr<UInputAction> InputAction;

	UPROPERTY(VisibleAnywhere, Category = "GameplayInputAbilityInfo")
	int32 InputID = 0;

	bool IsValid() const
	{
		return !GameplayAbilityClass.IsNull();
	}

	bool operator==(const FGameplayInputAbilityInfo& Other) const
	{
		return GameplayAbilityClass == Other.GameplayAbilityClass && InputAction == Other.InputAction;
	}

	bool operator!=(const FGameplayInputAbilityInfo& Other) const
	{
		return !operator==(Other);
	}

	friend uint32 GetTypeHash(const FGameplayInputAbilityInfo& Item)
	{
		return HashCombine(GetTypeHash(Item.GameplayAbilityClass), GetTypeHash(Item.InputAction));
	}
};

UCLASS()
class RAPID_API UGameplayAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TSet<FGameplayInputAbilityInfo> InputAbilities;

public:
	const TSet<FGameplayInputAbilityInfo>& GetInputAbilities() const { return InputAbilities; }

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
