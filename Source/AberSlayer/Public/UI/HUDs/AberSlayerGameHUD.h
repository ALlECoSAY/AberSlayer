// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "AberSlayerHUD.h"
#include "AberSlayerGameHUD.generated.h"

class UGameHUDMainWidget;
/**
 * 
 */
UCLASS()
class ABERSLAYER_API AAberSlayerGameHUD : public AAberSlayerHUD
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UGameHUDMainWidget> GameHUDMainWidgetClass;

	UPROPERTY()
	TObjectPtr<UGameHUDMainWidget> GameHUDMainWidget;

	
	
};
