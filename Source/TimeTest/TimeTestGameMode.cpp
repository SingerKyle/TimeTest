// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeTestGameMode.h"
#include "TimeTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATimeTestGameMode::ATimeTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
