// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#include "AberSlayer/Public/GameModes/AberSlayerGameMode.h"

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
