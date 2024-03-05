// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/EItem.h"
#include "InventorySlot.generated.h"


USTRUCT()
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EItem RealItemType = EItem::NONE;
	UPROPERTY(EditAnywhere)
	EItem AberItemType = EItem::NONE;

	UPROPERTY()
	TObjectPtr<AActor> RealItemActor = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> AberItemActor = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	int32 ItemCount = 1;
	
};