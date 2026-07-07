// Copyright yuanye 


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include"AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include"GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(50.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always); //do_rep_notify
	//这在注册属性并进行复制
	//COND_None：无条件进行复制
	//REPNOTIFY_Always：只要在服务器上设置值，就要进行复制
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute==GetHealthAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0.f,GetMaxHealth());
		UE_LOG(LogTemp,Warning,TEXT("Health:%f"),NewValue);
	}
	else if (Attribute==GetManaAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0.f,GetMaxMana());
		//UE_LOG(LogTemp,Warning,TEXT("Mana:%f"),NewValue);
	}
	
	
}
void UAuraAttributeSet::setEffetProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle=Data.EffectSpec.GetContext();   //获取效果上下文
	Props.SourceASC=Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();    //获取能力系统组件
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() &&Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())  //判断SourceASC,AbilityActorInfo,AvatarActor是否有效
	{
		Props.SourceAvatarActor=Props.SourceASC->AbilityActorInfo->AvatarActor.Get();    //获取AvatarActor角色
		Props.SourceController=Props.SourceASC->AbilityActorInfo->PlayerController.Get();   //获取控制器
		if (Props.SourceController==nullptr&&Props.SourceAvatarActor!=nullptr)  //控制器无效但是AvatarActor有效
		{
			if (const APawn*Pawn=Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController=Pawn->GetController();
			}
		}
		if (Props.SourceController) //控制器有效
		{
			Props.SourceCharacter=Cast<ACharacter>(Props.SourceController->GetPawn());   //获取Character
		}
		
	}
	if (Data.Target.AbilityActorInfo.IsValid()&&Data.Target.AbilityActorInfo->AvatarActor.IsValid())   //判断AbilityActorInfo，AvatarActor是否有效
	{
		Props.TargetAvatarActor=Data.Target.AbilityActorInfo->AvatarActor.Get(); //获取AvatarActor角色
		Props.TargetController=Data.Target.AbilityActorInfo->PlayerController.Get();  //获取控制器
		Props.TargetCharacter=Cast<ACharacter>(Props.TargetAvatarActor);              //获取character角色
		Props.TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor); //获取能力系统组件
		
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	/*if (Data.EvaluatedData.Attribute==GetHealthAttribute())
	{
		UE_LOG(LogTemp,Warning,TEXT("Health:%f"),GetHealth());
		UE_LOG(LogTemp,Warning,TEXT("Magnitude:%f"),Data.EvaluatedData.Magnitude);
	}
	*/
	FEffectProperties Props;
	setEffetProperties(Data,Props);
	
}


void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
	//作用是告诉能力系统这个属性的变化
	//记住旧值，可以在之后回滚的时候用到，还没有定义回滚函数
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}

