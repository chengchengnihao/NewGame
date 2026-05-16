// Copyright yuanye 


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Sphere=CreateDefaultSubobject<USphereComponent>("Sphere");
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
		Destroy();
}
}

void AAuraEffectActor::EndOverlay(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this,&AAuraEffectActor::OnOverlay);
	Sphere->OnComponentEndOverlap.AddDynamic(this,&AAuraEffectActor::EndOverlay);
}




