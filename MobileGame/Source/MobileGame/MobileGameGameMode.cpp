// Copyright Epic Games, Inc. All Rights Reserved.

#include "MobileGameGameMode.h"
#include "MobileGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMobileGameGameMode::AMobileGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


