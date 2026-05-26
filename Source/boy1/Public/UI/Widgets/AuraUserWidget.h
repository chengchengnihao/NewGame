// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOY1_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)  //将c++函数暴露给蓝图
	void SetWidgetController(UObject*InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject>WidgetController; //设置用来存储它的控件控制器的成员变量
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();  //在蓝图中设置的函数
	
};
