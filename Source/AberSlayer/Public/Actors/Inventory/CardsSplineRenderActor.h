// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/SplineMeshActor.h"
#include "CardsSplineRenderActor.generated.h"

class USplineComponent;

UCLASS()
class ABERSLAYER_API ACardsSplineRenderActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACardsSplineRenderActor();

	void UpdateRenderActors(TArray<TObjectPtr<AActor>> ActorsToIncludeInRender);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spline")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent;

	
	
	
};
