// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class ABERSLAYER_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// image widget
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "Inventory")
	TObjectPtr<UImage> InventoryImage;
	
};
