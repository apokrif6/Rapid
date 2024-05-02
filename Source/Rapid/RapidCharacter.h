// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RapidCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbilityInputConfig;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ARapidCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ARapidCharacter();

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Input")
	TObjectPtr<UGameplayAbilityInputConfig> GameplayAbilityInputConfig;

private:
	void InitializeGameplayAbilitySystem() const;

	void OnAbilityInputPressed(int32 InputID);

	void OnAbilityInputReleased(int32 InputID);
};
