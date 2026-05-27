// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"

#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FAuraWidgetControllerParams
{
	GENERATED_BODY();
	FAuraWidgetControllerParams(){}
	FAuraWidgetControllerParams(AAuraPlayerController*PC,AAuraPlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS)
	:PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){}
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AAuraPlayerController>PlayerController;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AAuraPlayerState>PlayerState;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAttributeSet>AttributeSet;
};
/**
 * 
 */

UCLASS()


class BOY1_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
   UFUNCTION(BlueprintCallable)
	void SetAuraWidgetControllerParams(const FAuraWidgetControllerParams &WCParams);
	
	virtual void BroadcastInitialValues();
protected:
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerState>PlayerState;  //为什么这个类型不需要前向声明呢？？因为头文件#include "CoreMinimal.h"包含了
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController>PlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet;
	
	
};
