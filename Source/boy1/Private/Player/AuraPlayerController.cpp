// Copyright yuanye 


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Runtime/ApplicationCore/Internal/GenericPlatform/CursorUtils.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit)return;//不懂
	LastActor=ThisActor;
	ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());//Cast大写！！
	/**
	 *Line trace from cursor. There are several scenarios:
	 * A: LastActor is null && ThisActor is null
	 *      -Do nothing
	 * B:LastActor is null,ThisActor is valid
	        -Highlight ThisActor
	 * C：Both actors are valid,and are the same actor
	 *           -Do nothing
	 * D：Both actors are valid,but LastActor!=ThisActor
	 *      -UnHighlight LastActor,and Highlight ThisActor
	 * E:LastActor is valid && ThisActor is null
	     -UnHighLight LastActor
	*/
	if (LastActor==nullptr)
	{
		if (ThisActor!=nullptr)
		{
			//case B
			ThisActor->HighlightActor();
		}
		else
		{
			//case A
		}
	}
	else
	{
		if (ThisActor==nullptr)
		{
			//case E
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor!=ThisActor)
			{
				//case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//case c
			}
		}
	}
}
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem*Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());  //设置子系统
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext,0);//通过子系统添加输入映射上下文
	
	bShowMouseCursor=true;//显示鼠标
	DefaultMouseCursor=EMouseCursor::Default;//设置鼠标
	FInputModeGameAndUI InputModeData;//默认有头文件FInputModeGameAndUI头文件，不用前向声明
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent*EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);//绑定IA和移动回调函数
	

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();//获取IA坐标值
	const FRotator Rotator=GetControlRotation();//获取旋转器，是获取摄像机的旋转器
	const FRotator YawRotator(0.f,Rotator.Yaw,0.f);
	
	const FVector ForwardDirection=FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);//获取世界向量
	const FVector RightDirection=FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
	
	if (APawn*ControlledPawn=Cast<APawn>(GetPawn()))
	{ 
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);//设置角色世界的移动方向
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
		
	}
	
	
}



