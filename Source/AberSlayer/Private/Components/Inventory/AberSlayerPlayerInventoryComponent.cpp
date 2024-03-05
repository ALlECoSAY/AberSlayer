// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "AberSlayer/Public/Components/Inventory/AberSlayerPlayerInventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerControllers/AberSlayerPlayerController.h"

#define SLOT_INDEX_DELTA -1

void UAberSlayerPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
	AddInputMappingContext();
	BindInputActionsToCallbackFunctions();
}

void UAberSlayerPlayerInventoryComponent::AddInputMappingContext()
{
	const auto PlayerController = CastChecked<AAberSlayerPlayerController>(GetOwner()->GetInstigatorController());
	const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MappingContext, InputMappingContextPriority);
}

void UAberSlayerPlayerInventoryComponent::RemoveInputMappingContext()
{
	const auto PlayerController = CastChecked<AAberSlayerPlayerController>(GetOwner()->GetInstigatorController());
	const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	check(Subsystem);
	Subsystem->RemoveMappingContext(MappingContext);
}

void UAberSlayerPlayerInventoryComponent::BindInputActionsToCallbackFunctions()
{	
	//get the player controller
	const auto PlayerController = CastChecked<AAberSlayerPlayerController>(GetOwner()->GetInstigatorController());
	//get the input component
	const auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent);
	
	
	EnhancedInputComponent->BindAction(ScrollActiveSlotIndexAction, ETriggerEvent::Triggered, this, &ThisClass::ScrollActiveSlot);

	EnhancedInputComponent->BindAction(ChooseActiveSlotIndexAction, ETriggerEvent::Triggered, this, &ThisClass::ChooseActiveSlot);

}

void UAberSlayerPlayerInventoryComponent::ScrollActiveSlot(const FInputActionValue& InputActionValue)
{
	const float Input = InputActionValue.Get<float>();
	ScrollActiveSlotIndexAccumulatedDelta += Input;
	
	if(FMath::Abs(ScrollActiveSlotIndexAccumulatedDelta) < ScrollActiveSlotIndexAccumulatedDeltaThreshold)
	{
		return;
	} 
	
	const int32 SlotIndexDelta = FMath::RoundToInt(ScrollActiveSlotIndexAccumulatedDelta/ScrollActiveSlotIndexAccumulatedDeltaThreshold);
	ScrollActiveSlotIndexAccumulatedDelta -= ScrollActiveSlotIndexAccumulatedDeltaThreshold * SlotIndexDelta;
	const int32 NewSlotIndex = ActiveSlotIndex + SlotIndexDelta;
	
	//validate
	const int32 NewSlotIndexValidated = FMath::Clamp(NewSlotIndex, 0, SlotsNumber - 1);
	
	SetActiveSlot(NewSlotIndexValidated);
}

void UAberSlayerPlayerInventoryComponent::ChooseActiveSlot(const FInputActionValue& InputActionValue)
{
	const float Input = InputActionValue.Get<float>();
	const int32 NewSlotIndex = FMath::RoundToInt(Input) + SLOT_INDEX_DELTA;

	//validate
	check(NewSlotIndex >= 0 && NewSlotIndex < SlotsNumber)
	
	SetActiveSlot(NewSlotIndex);
}

void UAberSlayerPlayerInventoryComponent::SetActiveSlot(int32 Index)
{
	check(Index >= 0 && Index < SlotsNumber);
	ActiveSlotIndex = Index;
	OnSlotChanged.Execute(Index);
	
#if WITH_EDITOR
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%hs %d"),__FUNCTION__, Index));
#endif
}
