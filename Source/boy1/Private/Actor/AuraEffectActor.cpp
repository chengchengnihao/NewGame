// Copyright yuanye 


#include "Actor/AuraEffectActor.h"

//#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
//#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	
	/*Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere->SetupAttachment(GetRootComponent());
	*/
}

/*void AAuraEffectActor::OnOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweetResult)
{
	if (IAbilitySystemInterface*AscInterface=Cast<IAbilitySystemInterface>(OtherActor))  //定义实现了接口的Actor
	{
		//访问角色的能力系统
		//把这段代码改成应用一个游戏效果（GameplayEffect），目前暂时用 const_cast 作为临时变通方案。
		const UAuraAttributeSet*AuraAttributeSet=Cast<UAuraAttributeSet>(AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		//获取属性会返回一个指向那个属性集的只读指针，可以通过强制转换来绕过这种只读属性
		UAuraAttributeSet*MutableAuraAttributeSet=const_cast<UAuraAttributeSet*>(AuraAttributeSet);  //解除const属性,打破封装
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth()+25.f);
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana()-25.f);
		Destroy();
}
}

void AAuraEffectActor::EndOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
*/
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	//Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlay);
	//Sphere->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlay);
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent*TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC==nullptr)return;
	
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle=TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle);
	//储存生效的游戏效果
	FActiveGameplayEffectHandle ActiveEffectHandle=TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	//查看是否为无限时长效果
	const bool bIsInfinite=EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy==EGameplayEffectDurationType::Infinite;
	
	if (bIsInfinite && InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy==EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent*TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetActor))return;
		
		TArray<FActiveGameplayEffectHandle>HandlesToRemove;
		
		for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair:ActiveEffectHandles)
		{
			if (TargetASC==HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle:HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}




