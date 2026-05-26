// Copyright yuanye 


#include "UI/Widgets/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController=InWidgetController;
	WidgetControllerSet();
}
