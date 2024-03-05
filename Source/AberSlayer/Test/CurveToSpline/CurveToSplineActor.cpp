// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "CurveToSplineActor.h"

#include "Components/SplineComponent.h"


// Sets default values
ACurveToSplineActor::ACurveToSplineActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CurveFloat = CreateDefaultSubobject<UCurveFloat>("Curve");
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");

	SplineComponent->bDrawDebug = true;
}

// Called when the game starts or when spawned
void ACurveToSplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACurveToSplineActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SplineMeshCount = SplineLength / SplineSectionLength;

	SplineComponent->ClearSplinePoints();

	for (int i = 0; i < SplineMeshCount; i++)
	{
		const float Alpha = (float)(i) / (float)((SplineMeshCount - 1));
		const float Y = CurveFloat->GetFloatValue(Alpha) * SplineHeigth;
		const float X =  i * SplineSectionLength; 
		FVector Location = FVector(X, Y, 0);
		FVector Tangent = FVector(0, 0, 0);
		FVector Scale = FVector(1, 1, 1);
		FRotator Rotation = FRotator(0, 0, 0);
		FTransform SplinePointTransform = FTransform(Rotation, Location, Scale);
		SplineComponent->AddSplinePoint(Location, ESplineCoordinateSpace::Local, false);
		//SplineComponent->SetTangentAtSplinePoint(i, Tangent, ESplineCoordinateSpace::Local, false);
	}

	SplineComponent->UpdateSpline();

	/*for (int i = 0; i < SplineMeshCount; i++)
	{
		UStaticMeshComponent* SplinePoint = NewObject<UStaticMeshComponent>(this, SplineMeshComponentClass);
		SplinePoint->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplinePoint->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
		
		const int InX = SplineComponent->GetLocationAtTime(i*SplineSectionLength, ESplineCoordinateSpace::Local).X;
		const int InY = SplineComponent->GetLocationAtTime(i*SplineSectionLength, ESplineCoordinateSpace::Local).Y;
		
		SplinePoint->SetRelativeLocation(FVector(InX, InY, i * SplineSectionLength));
		SplinePoints.Add(SplinePoint);
	}*/
}


