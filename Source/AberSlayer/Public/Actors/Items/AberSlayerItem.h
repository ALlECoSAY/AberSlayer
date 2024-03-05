// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EItem.h"

#include "AberSlayerItem.generated.h"

UCLASS()
class ABERSLAYER_API AAberSlayerItem : public AActor
{
	GENERATED_BODY()




protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	EItem ItemType = EItem::NONE;
	
};
