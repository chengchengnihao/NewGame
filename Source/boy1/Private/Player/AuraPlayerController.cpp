// Copyright yuanye 


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include"EnhancedInputComponent.h"
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates=true;
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
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);
	

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector=InputActionValue.Get<FVector2D>();
	const FRotator Rotator=InputActionValue.Get<FRotator>();
	const FRotator YawRotator(0.f,Rotator.Yaw,0.f);
	
	const FVector ForwardDirection=FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
	
	if (APawn*ControlledPawn=Cast<APawn>(GetPawn()))
	{ 
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
		
	}
	
	
}
