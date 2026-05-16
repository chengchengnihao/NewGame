// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"


/**
 * 
 */
UCLASS()
class BOY1_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//不需要写UFUNCTION()宏，因为它不需要在蓝图里调用，实现，也不需要引擎反射系统识别
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const override;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes")  
	//当服务器把 Health 同步到客户端时，自动调用客户端的 OnRep_Health() 函数。
	//大多数属性都需要这样做
	FGameplayAttributeData Health;   //Health是属性值不是指针，它存储于FGameplayAttributeData结构体中
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth; 
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana; 
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attributes")
	FGameplayAttributeData MaxMana; 
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth)const;//末尾的const作用是只读取数据，不修改任何成员变量
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana)const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)const;
	
	
};
