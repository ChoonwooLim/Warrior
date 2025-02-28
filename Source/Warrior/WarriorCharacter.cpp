// Copyright Epic Games, Inc. All Rights Reserved.

#include "WarriorCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CustomMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DebugHelper.h"


//////////////////////////////////////////////////////////////////////////
// AWarriorCharacter

AWarriorCharacter::AWarriorCharacter(const FObjectInitializer& ObjectInitializer)
/*AWarriorCharacter 생성자는 FObjectInitializer를 받아 부모 ACharacter를 초기화하는 역할을 함.*/

	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>(ACharacter::CharacterMovementComponentName))
	/*Super() 호출 시 SetDefaultSubobjectClass<UCustomMovementComponent>를 사용하여 기본 이동 컴포넌트를 UCustomMovementComponent로 교체함.
      ACharacter는 기본적으로 UCharacterMovementComponent를 사용하지만, 이를 UCustomMovementComponent로 변경하는 것.
      ACharacter::CharacterMovementComponentName은 기본 이동 컴포넌트의 이름(문자열)이며, 이를 UCustomMovementComponent로 대체함.*/
{
	// 캡슐 콜리전 크기 설정
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	/*CapsuleComponent의 크기를 설정.
      캡슐형 충돌체의 반지름(42.0f)과 높이(96.0f)를 지정. -> 결과: 캐릭터의 충돌 크기가 설정됨.*/
		
	// 컨트롤러 회전이 캐릭터에 영향을 미치지 않도록 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	/*컨트롤러가 회전할 때 캐릭터가 함께 회전하지 않도록 설정.
      카메라만 회전하도록 하고, 캐릭터는 입력 방향으로만 이동하도록 제어.
      결과: 컨트롤러 회전이 캐릭터 자체 회전에 영향을 주지 않음.*/

	// CustomMovementComponent 를 캐스팅하여 사용
	CustomMovementComponent = Cast<UCustomMovementComponent>(GetCharacterMovement());
	/*GetCharacterMovement()로 얻은 이동 컴포넌트를 UCustomMovementComponent로 캐스팅하여 CustomMovementComponent에 저장.
	  결과: CustomMovementComponent를 통해 UCustomMovementComponent의 멤버 변수 및 함수에 접근 가능.*/
	
	// 캐릭터의 이동 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	/*캐릭터가 입력 방향을 따라 회전하도록 설정.
      기본적으로 컨트롤러의 방향을 따라가는 것이 아니라, 이동 입력 방향으로 캐릭터가 회전하도록 만듦.*/

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	/*캐릭터의 회전 속도를 설정 (Yaw 축에서 초당 500도 회전).
       결과: 캐릭터가 이동 입력 방향을 따라 회전하며, 회전 속도는 초당 500도.*/

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// 이동 관련 세부 설정
	GetCharacterMovement()->JumpZVelocity = 700.f;
	// 점프 시 Z축 속도 설정
	GetCharacterMovement()->AirControl = 0.35f;
	// 공중에서 이동을 제어할 수 있는 정도 (0.0이면 공중 이동 불가능, 1.0이면 완전한 제어 가능).
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//걷기 속도의 최대값 (500의 속도로 걷기 가능).
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	//컨트롤러 입력이 최소일 때 걷기 속도를 20.f로 설정 (아날로그 입력 감지).
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	//걷기에서 멈출 때 감속하는 정도 (2000.f의 감속률 적용).
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	//공중에서 낙하할 때 감속하는 정도 (1500.f의 감속률 적용).

	// 카메라 붐(Spring Arm) 생성
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	/*Spring Arm 컴포넌트 생성 및 RootComponent에 부착.
      Spring Arm은 카메라를 플레이어 캐릭터에서 일정 거리 유지하도록 하는 역할.*/

	CameraBoom->TargetArmLength = 400.0f; 
	//캐릭터와 카메라 사이의 거리(400.f 단위).
	CameraBoom->bUsePawnControlRotation = true; 
	/*컨트롤러 회전이 Spring Arm에 적용되도록 설정.
      즉, 카메라는 컨트롤러를 따라 회전하지만, 캐릭터는 회전하지 않음.
      결과: 카메라가 캐릭터 뒤에서 따라오며, 컨트롤러의 회전 방향을 반영함.*/

	// 카메라 컴포넌트 생성 및 Spring Arm에 부착
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	/*카메라를 생성하고 Spring Arm 끝에 부착.
       SocketName을 사용하여 Spring Arm의 끝에 카메라를 배치.*/

	FollowCamera->bUsePawnControlRotation = false; 
	/*카메라가 Spring Arm에 의해 자동으로 움직이도록 설정 (카메라 자체는 컨트롤러의 회전에 영향받지 않음).
       결과: 캐릭터를 따라오는 3인칭 카메라 설정.*/
}

void AWarriorCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// CustomMovementComponent 초기화 (안전한 방식)
	CustomMovementComponent = Cast<UCustomMovementComponent>(GetCharacterMovement());

	if (!CustomMovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CustomMovementComponent is NULL in WarriorCharacter!"));
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void AWarriorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWarriorCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWarriorCharacter::Look);

		// climbing
		EnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Started, this, &AWarriorCharacter::OnClimbActionStarted);
	}
	
}

void AWarriorCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWarriorCharacter::OnClimbActionStarted(const FInputActionValue& Value)
{
	Debug::Print(TEXT("Climb Action Started"));
}

void AWarriorCharacter::StartFlying()
{
	if (!CustomMovementComponent) return;

	if (CustomMovementComponent->CheckFlightCondition() && GetCharacterMovement()->MovementMode != MOVE_Flying)
	{
		UE_LOG(LogTemp, Log, TEXT("Character is now flying."));
		CustomMovementComponent->SetMovementMode(MOVE_Flying);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Flight start blocked."));
	}
}

void AWarriorCharacter::StopFlying()
{
	if (!CustomMovementComponent) return;

	if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		UE_LOG(LogTemp, Log, TEXT("Character is stopping flight."));
		CustomMovementComponent->SetMovementMode(MOVE_Falling);
	}
}