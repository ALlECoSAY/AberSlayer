// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Aberrable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAberrable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABERSLAYER_API IAberrable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void OnAberrate(bool bIsAberrated) {PURE_VIRTUAL()};

};
