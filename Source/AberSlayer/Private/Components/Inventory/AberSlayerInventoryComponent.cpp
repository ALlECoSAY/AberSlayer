// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#include "AberSlayer/Public/Components/Inventory/AberSlayerInventoryComponent.h"

#include "GameModes/AberSlayerGameMode.h"


DEFINE_LOG_CATEGORY(LogAberSlayerInventoryComponent);

UAberSlayerInventoryComponent::UAberSlayerInventoryComponent()
{

	Slots.Reserve(SlotsNumber);

	
}

void UAberSlayerInventoryComponent::OnAberrate(bool bIsAberrated)
{
	UE_LOG(LogAberSlayerInventoryComponent, Log, TEXT("'%s' Aberration state changed to '%d'"), *GetNameSafe(this), bIsAberrated);
	
}

void UAberSlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const auto GameMode = GetWorld()->GetAuthGameMode<AAberSlayerGameMode>();
	check(GameMode)

	GameMode->OnAberrateDelegate.AddUObject(this, &ThisClass::OnAberrate);
	
	
	
}
