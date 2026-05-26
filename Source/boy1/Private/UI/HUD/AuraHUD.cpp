// Copyright yuanye 


#include "UI/HUD/AuraHUD.h"
struct FAuraWidgetControllerParams;
#include "Dataflow/DataflowOverlay.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController==nullptr)
	{
		OverlayWidgetController=NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetAuraWidgetControllerParams(WCParams);
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(AAuraPlayerController* PC, AAuraPlayerState* PS, UAbilitySystemComponent* ASC,
	UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass is uninitialed,please fill out in BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass is uninitialed,please fill out in BP_AuraHUD"));
	UUserWidget*Widget=CreateWidget(GetWorld(),OverlayWidgetClass);
	OverlayWidget=Cast<UAuraUserWidget>(Widget);
	
	const FAuraWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	
	UOverlayWidgetController*WidgetController=GetOverlayWidgetController(WidgetControllerParams);
	//记住啊，哼哼，难受死了，要记得创建一个传入部件控制器啊，这样才能传入控制器啊啊
	
	OverlayWidget->SetWidgetController(WidgetController);
	Widget->AddToViewport();
	
}


