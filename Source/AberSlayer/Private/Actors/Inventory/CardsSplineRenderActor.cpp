// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "Actors/Inventory/CardsSplineRenderActor.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Components/SplineComponent.h"


// Sets default values
ACardsSplineRenderActor::ACardsSplineRenderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SceneRoot->SetupAttachment(RootComponent);

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(SceneRoot);

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCaptureComponent->SetupAttachment(SceneRoot);
	SceneCaptureComponent->ShowOnlyActorComponents(this,true);
	//todo show cards in render
}

void ACardsSplineRenderActor::UpdateRenderActors(TArray<TObjectPtr<AActor>> ActorsToIncludeInRender)
{
	SceneCaptureComponent->ShowOnlyActors = ActorsToIncludeInRender;
}

// Called when the game starts or when spawned
void ACardsSplineRenderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardsSplineRenderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

