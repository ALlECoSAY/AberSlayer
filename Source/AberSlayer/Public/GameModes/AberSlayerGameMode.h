// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AberSlayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAberSlayerGameMode, Log, All);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAberrateSignature, bool);

UCLASS(minimalapi)
class AAberSlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAberSlayerGameMode();

	void Aberrate();

	FOnAberrateSignature OnAberrateDelegate;

private:
	
	UPROPERTY()
	bool bIsAberrated = false;
	
};



