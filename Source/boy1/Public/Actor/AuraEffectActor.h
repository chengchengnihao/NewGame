// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;

UCLASS()
class BOY1_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraEffectActor();
	
	UFUNCTION()
    virtual void OnOverlay(UPrimitiveComponent*OverlappedComponent,AActor*OtherActor,UPrimitiveComponent*OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweetResult);
   UFUNCTION()
	virtual void EndOverlay(UPrimitiveComponent*OverlappedComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:

	virtual void BeginPlay() override;
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>Sphere;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>Mesh;
	


};
