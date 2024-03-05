// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CurveToSplineActor.generated.h"

class USplineComponent;


UCLASS()
class ABERSLAYER_API ACurveToSplineActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACurveToSplineActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TObjectPtr<UCurveFloat> CurveFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float SplineLength = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float SplineSectionLength = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float SplineHeigth = 1000.0f;
	
	int SplineMeshCount;

	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>> SplinePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TSubclassOf<UStaticMeshComponent> SplineMeshComponentClass;

};
