// Copyright yuanye 


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet*AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChangedSignature.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedSignature.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChangedSignature.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChangedSignature.Broadcast(AuraAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
   const UAuraAttributeSet*AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).
	AddUObject(this,& UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).
    AddUObject(this,& UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).
	AddUObject(this,& UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).
	AddUObject(this,& UOverlayWidgetController::MaxManaChanged);
	
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer&AssetTages)//this用来捕捉此类中的所有信息，是的匿名函数内部可以使用这些信息
	{
		for (const auto &Tag:AssetTages)
		{
			//const FString Msg=FString::Printf(TEXT("GE Tag:%s"),*Tag.ToString());//打印的时候使用过的
			//GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Green,Msg);
			FGameplayTag MessageTag=FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow*Row=GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);//因为使用的是模板函数，所以调用的时候必须传入类型
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
			GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);//因为使用的是模板函数，所以调用的时候必须传入类型
			
		}
	}	
	);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChangedSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChangedSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChangedSignature.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChangedSignature.Broadcast(Data.NewValue);
}


