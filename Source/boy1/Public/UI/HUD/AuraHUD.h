// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "AuraHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOY1_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget>OverlayWidget;
	
	UOverlayWidgetController*GetOverlayWidgetController(const FAuraWidgetControllerParams &WCParams);
	
	void InitOverlay(AAuraPlayerController*PC,AAuraPlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS);

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget>OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>OverlayWidgetControllerClass;
	
	
};
