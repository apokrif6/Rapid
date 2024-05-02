// Copyright Epic Games, Inc. All Rights Reserved.

#include "RapidGameMode.h"
#include "RapidCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARapidGameMode::ARapidGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
