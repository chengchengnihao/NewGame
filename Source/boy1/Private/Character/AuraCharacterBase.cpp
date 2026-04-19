// Copyright yuanye 


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
 
	PrimaryActorTick.bCanEverTick = false;
    Weawpon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


