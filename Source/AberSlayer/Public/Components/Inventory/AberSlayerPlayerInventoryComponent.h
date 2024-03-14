// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "AberSlayerInventoryComponent.h"
#include "InputActionValue.h"
#include "Actors/Inventory/AberSlayerInventoryCard.h"
#include "Actors/Inventory/CardsSplineRenderActor.h"
#include "Components/TimelineComponent.h"
#include "AberSlayerPlayerInventoryComponent.generated.h"

class AAberSlayerItem;
class UInputMappingContext;
class UInputAction;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveSlotChangedSignature, int32 /*SlotIndex*/);

UCLASS(Blueprintable, BlueprintType, ClassGroup=(AberSlayer), meta=(BlueprintSpawnableComponent))
class ABERSLAYER_API UAberSlayerPlayerInventoryComponent : public UAberSlayerInventoryComponent
{
	GENERATED_BODY()

public:

	FOnActiveSlotChangedSignature OnActiveSlotChanged;

	UAberSlayerPlayerInventoryComponent();
	
protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Input mappings management
	void AddInputMappingContext();
	void RemoveInputMappingContext();
	void BindInputActionsToCallbackFunctions();

	
	void ScrollActiveSlot(const FInputActionValue& InputActionValue);
	void ChooseActiveSlot(const FInputActionValue& InputActionValue);

	void SetActiveSlot(int32 Index);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateCardsSplineUI();

	UFUNCTION(BlueprintNativeEvent)
	void CardsAnimationUpdate(float Value);
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAberSlayerInventoryCard> CardClass;

	// Needs to be set up in level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACardsSplineRenderActor> CardsSplineRenderActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI", meta = (AllowPrivateAccess = "true", ClampMin = "0",ClampMax = "0.4999"))
	float CardsMargin = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI", meta = (AllowPrivateAccess = "true", ClampMin = "0",ClampMax = "0.4999"))
	float CardsSpacing = 0.1f;

	UPROPERTY(BlueprintReadWrite)
	float CardsPadding = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI", meta = (AllowPrivateAccess = "true"))
	float CardsOverlapOffset = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI", meta = (AllowPrivateAccess = "true"))
	float ActiveCardHeightOffset = 4.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory|UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveFloat> CardsAnimationCurve;

	float CardsAnimationProgress = 0.f;

	FTimeline CardsAnimationTimeline;

	TArray<float> CardsCashedSplineOldTimeValues;
	TArray<float> CardsCashedSplineCurrentTimeValues;
	TArray<float> CardsCashedSplineNewTimeValues;
	TArray<float> CardsCashedSplineOldHeightValues;
	TArray<float> CardsCashedSplineCurrentHeightValues;
	TArray<float> CardsCashedSplineNewHeightValues;
	
};
