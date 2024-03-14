// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Actors/Inventory/AberSlayerInventoryCard.h"
#include "Actors/Items/EItem.h"
#include "InventorySlot.generated.h"


class ACardsSplineRenderActor;

USTRUCT(Blueprintable,BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItem RealItemType = EItem::NONE;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItem AberItemType = EItem::NONE;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> RealItemActor = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> AberItemActor = nullptr;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AAberSlayerInventoryCard> CardActor = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemCount = 1;
	
};