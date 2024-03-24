// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySlot.h"
#include "Aberrable/Aberrable.h"
#include "AberSlayerInventoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAberSlayerInventoryComponent, Log, All);

class USplineComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryChangedSignature, TArray<FInventorySlot> /*Slots*/);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(AberSlayer), meta=(BlueprintSpawnableComponent))
class ABERSLAYER_API UAberSlayerInventoryComponent : public UActorComponent, public IAberrable
{

private:
	GENERATED_BODY()

public:
	FOnInventoryChangedSignature OnInventoryChanged;
	
public:
	UAberSlayerInventoryComponent();
	
	virtual void OnAberrate(bool bIsAberrated) override;
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true"))
	int32 SlotsNumber = 6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FInventorySlot> Slots;	

	
};


