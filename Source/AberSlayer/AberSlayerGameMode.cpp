// Copyright Epic Games, Inc. All Rights Reserved.

#include "AberSlayerGameMode.h"
#include "AberSlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAberSlayerGameMode::AAberSlayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
