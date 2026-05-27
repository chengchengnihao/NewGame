// Copyright yuanye 


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetAuraWidgetControllerParams(const FAuraWidgetControllerParams& WCParams)
{
	PlayerState=WCParams.PlayerState;
	PlayerController=WCParams.PlayerController;
	AbilitySystemComponent=WCParams.AbilitySystemComponent;
	AttributeSet=WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{
	
}

