// Copyright yuanye 


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
 
	PrimaryActorTick.bCanEverTick = false;
    Weapon=CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//CreateDefaultSubobject需要FName,FName不需要TEXT宏，FString需要TEXT宏，FString是给人看，FName是给引擎看，所以只用存编号
	//起名、查找、插槽、组件名 → FName
	//显示、打印、拼接、内容 → FString
	//左边的weapon是在c++中被调用
	//右边的weapon在蓝图中被创建
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


