// Copyright yuanye 


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet*AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChangedSignature.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedSignature.Broadcast(AuraAttributeSet->GetMaxHealth());
   
}
