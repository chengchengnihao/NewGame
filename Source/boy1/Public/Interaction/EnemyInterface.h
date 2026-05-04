// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface  //只是标记，告诉UE这是一个接口，不可以实现功能
{
	GENERATED_BODY()

};

/**
 * 
 */
class BOY1_API IEnemyInterface   //实现功能，可以写纯虚拟函数
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighlightActor()=0;//创建纯虚拟函数
	virtual void UnHighlightActor()=0;
};
