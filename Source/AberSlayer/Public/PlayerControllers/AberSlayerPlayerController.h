// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AberSlayerPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

DECLARE_LOG_CATEGORY_EXTERN(LogAberSlayerPlayerController, Log, All);

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ABERSLAYER_API AAberSlayerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Aberrate();

	UFUNCTION()
	void OnAberrate(bool bIsAberrated);
	
	virtual void SetupInputComponent() override;

protected:
#pragma region Input

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> ControllerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AberrateAction;
	
#pragma endregion Input
	
	
	
};
