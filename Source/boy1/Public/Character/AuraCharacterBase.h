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


};
