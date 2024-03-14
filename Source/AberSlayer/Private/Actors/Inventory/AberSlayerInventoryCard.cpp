// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "Actors/Inventory/AberSlayerInventoryCard.h"


// Sets default values
AAberSlayerInventoryCard::AAberSlayerInventoryCard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CardMesh"));
	CardMesh->SetupAttachment(SceneRoot);
	
	
}

// Called when the game starts or when spawned
void AAberSlayerInventoryCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAberSlayerInventoryCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

