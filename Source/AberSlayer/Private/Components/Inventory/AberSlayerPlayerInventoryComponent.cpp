// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "AberSlayer/Public/Components/Inventory/AberSlayerPlayerInventoryComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Characters/AberSlayerCharacter.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/AberSlayerPlayerController.h"

#define SLOT_INDEX_DELTA -1

UAberSlayerPlayerInventoryComponent::UAberSlayerPlayerInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	CardsAnimationTimeline = FTimeline{};

	
	CardsCashedSplineOldTimeValues.Init(0.f, SlotsNumber);
	CardsCashedSplineNewTimeValues.Init(0.f, SlotsNumber);
	CardsCashedSplineCurrentTimeValues.Init(0.f, SlotsNumber);
	CardsCashedSplineOldHeightValues.Init(0.f, SlotsNumber);
	CardsCashedSplineCurrentHeightValues.Init(0.f, SlotsNumber);
	CardsCashedSplineNewHeightValues.Init(0.f, SlotsNumber);
}

void UAberSlayerPlayerInventoryComponent::BeginPlay()
{
	check(CardClass);
	Super::BeginPlay();

	FOnTimelineFloat CardsAnimationUpdateDelegate;
	CardsAnimationUpdateDelegate.BindUFunction(this, FName("CardsAnimationUpdate"));
	check(CardsAnimationCurve);
	const auto EndTime = CardsAnimationCurve->FloatCurve.GetLastKey().Time;
	CardsAnimationTimeline.SetNewTime(0.f);
	CardsAnimationTimeline.SetTimelineLength(EndTime);
	CardsAnimationTimeline.AddInterpFloat(CardsAnimationCurve, CardsAnimationUpdateDelegate, FName("CardsAnimationUpdate"));

	
	AddInputMappingContext();
	BindInputActionsToCallbackFunctions();

	CardsSplineRenderActor = CastChecked<ACardsSplineRenderActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACardsSplineRenderActor::StaticClass()));
	check(CardsSplineRenderActor)
	
	
	//todo redo slots
	for (int32 i = 0; i < SlotsNumber; i++)
	{
		const auto SlotId = Slots.Add(FInventorySlot());
		FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const auto Card = GetWorld()->SpawnActor<AAberSlayerInventoryCard>(CardClass, SpawnParameters);
		Slots[SlotId].CardActor = Card;
	}
	
	
	UpdateCardsSplineUI();	
}

void UAberSlayerPlayerInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if WITH_EDITOR
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(44, 1.f, FColor::Red, FString::Printf(TEXT("%hs"), __FUNCTION__));
#endif
	
	if(CardsAnimationTimeline.IsPlaying())
	{
		CardsAnimationTimeline.TickTimeline(DeltaTime);
	}
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
	OnActiveSlotChanged.Broadcast(Index);
	UpdateCardsSplineUI();
#if WITH_EDITOR
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%hs %d"),__FUNCTION__, Index));
#endif
}

void UAberSlayerPlayerInventoryComponent::CardsAnimationUpdate_Implementation(float Value)
{
	const auto NumOfSlots = Slots.Num();
	if(!NumOfSlots) { return; }
	check(CardsSplineRenderActor)
	const auto CardsSpline = CardsSplineRenderActor->SplineComponent;
	check(CardsSpline)
	
	for(int i = 0; i < NumOfSlots; i++)
	{
		const auto& Card = Slots[i].CardActor;
		
		const auto CardTimeOnSpline = FMath::Lerp(CardsCashedSplineOldTimeValues[i], CardsCashedSplineNewTimeValues[i], Value);
		CardsCashedSplineCurrentTimeValues[i] = CardTimeOnSpline;
		const auto SlotLocation = CardsSpline->GetLocationAtTime(CardTimeOnSpline, ESplineCoordinateSpace::World);
		const auto SlotRotation = CardsSpline->GetRotationAtTime(CardTimeOnSpline, ESplineCoordinateSpace::World);
		Card->SetActorLocation(SlotLocation);
		Card->SetActorRotation(SlotRotation);

		const auto CardHeightOffset = FMath::Lerp(CardsCashedSplineOldHeightValues[i], CardsCashedSplineNewHeightValues[i], Value);
		CardsCashedSplineCurrentHeightValues[i] = CardHeightOffset;
		const auto CardLocalYOffset = CardsOverlapOffset * i;
		Card->CardMesh->SetRelativeLocation(FVector(0.f, CardLocalYOffset, CardHeightOffset));
	}
}

void UAberSlayerPlayerInventoryComponent::UpdateCardsSplineUI_Implementation()
{

	const auto NumOfSlots = Slots.Num();
	if(!NumOfSlots) { return; }
	
	TArray<TObjectPtr<AActor>> ActorsToIncludeInRender;

	CardsPadding = (1.f - CardsMargin * 2 - CardsSpacing * (NumOfSlots - 1)) / 2.f;
	check(CardsPadding>= 0.f);
	
	for(int i = 0; i < NumOfSlots; i++)
	{
		const auto& Card = Slots[i].CardActor;
		const auto CardActiveTimeOffset = i > ActiveSlotIndex ? CardsMargin : (-0.5f * CardsMargin);
		const auto CardTimeOnSpline = CardsMargin + CardsPadding + CardsSpacing * i + CardActiveTimeOffset;
		CardsCashedSplineOldTimeValues[i] = CardsCashedSplineCurrentTimeValues[i];
		CardsCashedSplineNewTimeValues[i] = CardTimeOnSpline;
		const auto CardHeight = i == ActiveSlotIndex ? ActiveCardHeightOffset : 0.f;
		CardsCashedSplineOldHeightValues[i] = CardsCashedSplineCurrentHeightValues[i];
		CardsCashedSplineNewHeightValues[i] = CardHeight;
		
		ActorsToIncludeInRender.Add(Card);
	}
	CardsSplineRenderActor->UpdateRenderActors(ActorsToIncludeInRender);

	CardsAnimationTimeline.PlayFromStart();
}
