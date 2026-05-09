// Copyright yuanye 


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include"AbilitySystem/AuraAttributeSet.h"
#include "boy1/boy1.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	//bHighlighted=true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	/*定义AbilitySystemComponent和AttributeSet*/
	AbilitySystemComponent=CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");//alt+enter自动添加头文件
	AbilitySystemComponent->SetIsReplicated(true); //不知道为什么AttributeSet不需要被复制
	
	AttributeSet=CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void AAuraEnemy::UnHighlightActor()
{
	//bHighlighted=false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

}
