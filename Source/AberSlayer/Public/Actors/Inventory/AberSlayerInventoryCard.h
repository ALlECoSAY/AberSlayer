// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AberSlayerInventoryCard.generated.h"

UCLASS()
class ABERSLAYER_API AAberSlayerInventoryCard : public AActor
{
	GENERATED_BODY()

public:
	AAberSlayerInventoryCard();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UStaticMeshComponent> CardMesh;

	
	
};
