// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#include "AberSlayer/Public/GameModes/AberSlayerGameMode.h"

#include "UObject/ConstructorHelpers.h"

DEFINE_LOG_CATEGORY(LogAberSlayerGameMode);

AAberSlayerGameMode::AAberSlayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AAberSlayerGameMode::Aberrate()
{
	UE_LOG(LogAberSlayerGameMode, Warning, TEXT("Aberration state changed to '%d'"), bIsAberrated);
	bIsAberrated = !bIsAberrated;
	OnAberrateDelegate.Broadcast(bIsAberrated);
}
