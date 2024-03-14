// Aleksey Pushkaryov t.me/all_eco_say Acerola game jam 1


#include "UI/HUDs/AberSlayerGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widgets/GameHUDMainWidget.h"

void AAberSlayerGameHUD::BeginPlay()
{
	Super::BeginPlay();

	// Add GameHUDMainWidget to the viewport
	if (GameHUDMainWidgetClass)
	{
		GameHUDMainWidget = CreateWidget<UGameHUDMainWidget>(GetWorld(), GameHUDMainWidgetClass);
		if (GameHUDMainWidget)
		{
			GameHUDMainWidget->AddToViewport();
		}
	}
	
}
