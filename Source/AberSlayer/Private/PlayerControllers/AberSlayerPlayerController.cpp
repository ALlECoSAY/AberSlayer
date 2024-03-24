// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "PlayerControllers/AberSlayerPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameModes/AberSlayerGameMode.h"

DEFINE_LOG_CATEGORY(LogAberSlayerPlayerController);

void AAberSlayerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const auto GameMode = GetWorld()->GetAuthGameMode<AAberSlayerGameMode>();
	check(GameMode)

	GameMode->OnAberrateDelegate.AddUObject(this, &ThisClass::OnAberrate);
	
}

void AAberSlayerPlayerController::Aberrate()
{
	const auto GameMode = GetWorld()->GetAuthGameMode<AAberSlayerGameMode>();
	check(GameMode)

	GameMode->Aberrate();	
}

void AAberSlayerPlayerController::OnAberrate(bool bIsAberrated)
{
	UE_LOG(LogAberSlayerPlayerController, Log, TEXT("'%s' Aberration state changed to '%d'"), *GetNameSafe(this), bIsAberrated);
	
}

void AAberSlayerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ControllerMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(AberrateAction, ETriggerEvent::Triggered, this, &ThisClass::Aberrate);
	}
	else
	{
		UE_LOG(LogAberSlayerPlayerController, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}
