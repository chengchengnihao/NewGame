// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class BOY1_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent*GetAbilitySystemComponent()const override;
	UAttributeSet*GetAttributes() const {return AttributeSet;}//如果不需要被重写，不加 virtual
protected:
	/*声明AbilitySystemComponent和AttributeSet*/
	UPROPERTY();
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY();
	TObjectPtr<UAttributeSet>AttributeSet;
};
