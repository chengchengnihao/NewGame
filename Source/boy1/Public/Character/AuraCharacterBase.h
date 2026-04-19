// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)//抽象类说明符，会使得类不被拖入关卡内
class BOY1_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent>Weapon;
	//T对象指针包装器，打包构建和原始指针行为一致，在编辑器中，还有访问跟踪和可选的延迟加载功能
	//访问跟踪是监控指针被访问或解引用的频率
	//延迟加载：程序实际需要或使用前，不加载资产

};
