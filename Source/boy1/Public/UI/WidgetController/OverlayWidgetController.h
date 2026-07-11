// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;

//创建一个行，然后才能够在UE里头创建行对应的数据表
USTRUCT(BlueprintType)//这个到了里头就是可以被当成一个行类型了
struct FUIWidgetRow:public FTableRowBase  //struct和public都是小写
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag=FGameplayTag();//元素一：基本标签
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message=FText();//元素二：标签文本，到时候显示在屏幕上的
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget>MessageWidget;//元素三：用户控件,因为还没有定义它，所以使用class
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D*Image=nullptr;//元素四：图案
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature,float,NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature,float,NewMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);



/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class BOY1_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChangedSignature;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChangedSignature;
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChangedSignature;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChangedSignature;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;
	

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UDataTable>MessageWidgetDataTable;//定义一个信息数据表的插槽
	
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
	
	template<typename T>
	T*GetDataTableRowByTag(UDataTable*DataTable,const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)  //声明一个模板类型，来查找数据表中的行信息
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
