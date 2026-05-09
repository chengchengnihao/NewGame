// Copyright yuanye 


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->bSnapToPlaneAtStart=true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationYaw=false;
	bUseControllerRotationRoll=false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	/*Init Ability Actor Info in Server*/
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	/*Init Ability Actor Info in Client*/
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState=GetPlayerState<AAuraPlayerState>(); //这个模板函数可以传入PlayerState类型来获取相应的返回类型
	check(AuraPlayerState);
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState,this);
	AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet=AuraPlayerState->GetAttributes();
}
