// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BOY1_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	/*Enemy Interface*/
	virtual void HighlightActor() override;//重写纯虚拟函数
	virtual void UnHighlightActor() override;
	/*End Enemy Interface*/
	
	//UPROPERTY(BlueprintReadOnly)
	//bool bHighlighted=false;
protected:
	virtual void BeginPlay()override;

};
