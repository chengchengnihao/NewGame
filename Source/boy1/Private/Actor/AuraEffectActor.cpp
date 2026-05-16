// Copyright yuanye 


#include "Actor/AuraEffectActor.h"

#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere->SetupAttachment(Mesh);
	

}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}




