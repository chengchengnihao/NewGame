// Copyright yuanye 


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include"AbilitySystem/AuraAttributeSet.h"
AAuraPlayerState::AAuraPlayerState()
{
	/*定义AbilitySystemComponent和AttributeSet*/
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");//alt+enter自动添加头文件
	AbilitySystemComponent->SetIsReplicated(true);
	
	
	AttributeSet=CreateDefaultSubobject<UAttributeSet>("AttributeSet");
	NetUpdateFrequency=100.f;
	
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
