// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySlot.h"
#include "AberSlayerInventoryComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(AberSlayer), meta=(BlueprintSpawnableComponent))
class ABERSLAYER_API UAberSlayerInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UAberSlayerInventoryComponent();

	
	
protected:	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true"))
	int32 SlotsNumber = 6;

	UPROPERTY(VisibleAnywhere)
	TArray<FInventorySlot> Slots;	
	
};


