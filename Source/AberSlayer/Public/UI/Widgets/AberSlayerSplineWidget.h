// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SplineComponent.h"
#include "AberSlayerSplineWidget.generated.h"

/**
 * 
 */
UCLASS()
class ABERSLAYER_API UAberSlayerSplineWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<USplineMetadata> SplineMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TSubclassOf<UUserWidget> FillerWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TObjectPtr<UCurveFloat> FloatCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float SplineLength = 1000.0f;

	//todo delete debug only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	float SplineSectionLength = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline|Roll Motion")
	TObjectPtr<UCurveFloat> Y_AxisFactorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline|Roll Motion")
	TObjectPtr<UCurveFloat> X_AxisFactorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	int32 NumberOfWidgets = 6;
	
};
