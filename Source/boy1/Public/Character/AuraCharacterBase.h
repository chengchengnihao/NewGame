// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)//抽象类说明符，会使得类不被拖入关卡内
class BOY1_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent*GetAbilitySystemComponent()const override;
	UAttributeSet*GetAttributes() const {return AttributeSet;}//如果不需要被重写，不加 virtual
	
protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent>Weapon;//这里和之前不一样，这里是在直接设置一个武器组件，之前没有
	//T对象指针包装器，打包构建和原始指针行为一致，在编辑器中，还有访问跟踪和可选的延迟加载功能
	//访问跟踪是监控指针被访问或解引用的频率
	//延迟加载：程序实际需要或使用前，不加载资产
	
	/*声明AbilitySystemComponent和AttributeSet*/
	UPROPERTY();
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;
	UPROPERTY();
	TObjectPtr<UAttributeSet>AttributeSet;
};
