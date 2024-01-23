// Copyright Epic Games, Inc. All Rights Reserved.

#include "SchmooveGameMode.h"
#include "SchmooveCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASchmooveGameMode::ASchmooveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
