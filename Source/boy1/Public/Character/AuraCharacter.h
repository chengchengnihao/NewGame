// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BOY1_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override; //在声明里头它们是在public里头的
	virtual void OnRep_PlayerState() override;
private:
	void InitAbilityActorInfo();
};
