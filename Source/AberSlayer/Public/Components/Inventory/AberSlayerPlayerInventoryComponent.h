// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "AberSlayerInventoryComponent.h"
#include "InputActionValue.h"
#include "AberSlayerPlayerInventoryComponent.generated.h"

class UInputMappingContext;
class UInputAction;
DECLARE_DELEGATE_OneParam(FOnSlotChangedSignature, int32 /*SlotIndex*/);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(AberSlayer), meta=(BlueprintSpawnableComponent))
class ABERSLAYER_API UAberSlayerPlayerInventoryComponent : public UAberSlayerInventoryComponent
{
	GENERATED_BODY()

public:

	FOnSlotChangedSignature OnSlotChanged;

protected:
	virtual void BeginPlay() override;

	
	
	// Input mappings management
	void AddInputMappingContext();
	void RemoveInputMappingContext();
	void BindInputActionsToCallbackFunctions();

	
	void ScrollActiveSlot(const FInputActionValue& InputActionValue);
	void ChooseActiveSlot(const FInputActionValue& InputActionValue);

	void SetActiveSlot(int32 Index);
	
protected:
#pragma region Input
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ScrollActiveSlotIndexAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ChooseActiveSlotIndexAction;
	
	UPROPERTY(EditAnywhere, Category= Input,  meta = (AllowPrivateAccess = "true"))
	int InputMappingContextPriority = 1;

	float ScrollActiveSlotIndexAccumulatedDelta = 0.f;

	// To change the sensitivity of the scroll, ether adjust this value, or go to IA_Scroll asset and change the Scalar modifier
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	float ScrollActiveSlotIndexAccumulatedDeltaThreshold = 10.f;
	
#pragma endregion

	UPROPERTY(VisibleAnywhere)
	int32 ActiveSlotIndex = -1;

};
