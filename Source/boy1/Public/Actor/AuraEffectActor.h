// Copyright yuanye 

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include"GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType) 
enum class EEffectRemovalPolicy:uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class BOY1_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AAuraEffectActor();
	
	/*UFUNCTION()
    virtual void OnOverlay(UPrimitiveComponent*OverlappedComponent,AActor*OtherActor,UPrimitiveComponent*OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweetResult);
   UFUNCTION()
	virtual void EndOverlay(UPrimitiveComponent*OverlappedComponent, AActor*OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
*/
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor*TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor*TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor*TargetActor);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	bool bDestroyOnEffectRemoval=false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
    TSubclassOf<UGameplayEffect>InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect>DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	TSubclassOf<UGameplayEffect>InfiniteGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy=EEffectRemovalPolicy::RemoveOnEndOverlap;
	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*>ActiveEffectHandles;
	
private:
	
	/*UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>Sphere;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>Mesh;
	*/


};
