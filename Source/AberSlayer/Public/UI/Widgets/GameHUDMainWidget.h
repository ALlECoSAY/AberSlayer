// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDMainWidget.generated.h"

class UInventoryWidget;
/**
 * 
 */
UCLASS()
class ABERSLAYER_API UGameHUDMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "Inventory")
	TObjectPtr<UInventoryWidget> InventoryWidget;
	
};
