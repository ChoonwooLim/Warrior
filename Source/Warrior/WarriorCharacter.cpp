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
/*AWarriorCharacter �����ڴ� FObjectInitializer�� �޾� �θ� ACharacter�� �ʱ�ȭ�ϴ� ������ ��.*/

	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>(ACharacter::CharacterMovementComponentName))
	/*Super() ȣ�� �� SetDefaultSubobjectClass<UCustomMovementComponent>�� ����Ͽ� �⺻ �̵� ������Ʈ�� UCustomMovementComponent�� ��ü��.
      ACharacter�� �⺻������ UCharacterMovementComponent�� ���������, �̸� UCustomMovementComponent�� �����ϴ� ��.
      ACharacter::CharacterMovementComponentName�� �⺻ �̵� ������Ʈ�� �̸�(���ڿ�)�̸�, �̸� UCustomMovementComponent�� ��ü��.*/
{
	// ĸ�� �ݸ��� ũ�� ����
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	/*CapsuleComponent�� ũ�⸦ ����.
      ĸ���� �浹ü�� ������(42.0f)�� ����(96.0f)�� ����. -> ���: ĳ������ �浹 ũ�Ⱑ ������.*/
		
	// ��Ʈ�ѷ� ȸ���� ĳ���Ϳ� ������ ��ġ�� �ʵ��� ����
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	/*��Ʈ�ѷ��� ȸ���� �� ĳ���Ͱ� �Բ� ȸ������ �ʵ��� ����.
      ī�޶� ȸ���ϵ��� �ϰ�, ĳ���ʹ� �Է� �������θ� �̵��ϵ��� ����.
      ���: ��Ʈ�ѷ� ȸ���� ĳ���� ��ü ȸ���� ������ ���� ����.*/

	// CustomMovementComponent �� ĳ�����Ͽ� ���
	CustomMovementComponent = Cast<UCustomMovementComponent>(GetCharacterMovement());
	/*GetCharacterMovement()�� ���� �̵� ������Ʈ�� UCustomMovementComponent�� ĳ�����Ͽ� CustomMovementComponent�� ����.
	  ���: CustomMovementComponent�� ���� UCustomMovementComponent�� ��� ���� �� �Լ��� ���� ����.*/
	
	// ĳ������ �̵� ����
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	/*ĳ���Ͱ� �Է� ������ ���� ȸ���ϵ��� ����.
      �⺻������ ��Ʈ�ѷ��� ������ ���󰡴� ���� �ƴ϶�, �̵� �Է� �������� ĳ���Ͱ� ȸ���ϵ��� ����.*/

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	/*ĳ������ ȸ�� �ӵ��� ���� (Yaw �࿡�� �ʴ� 500�� ȸ��).
       ���: ĳ���Ͱ� �̵� �Է� ������ ���� ȸ���ϸ�, ȸ�� �ӵ��� �ʴ� 500��.*/

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// �̵� ���� ���� ����
	GetCharacterMovement()->JumpZVelocity = 700.f;
	// ���� �� Z�� �ӵ� ����
	GetCharacterMovement()->AirControl = 0.35f;
	// ���߿��� �̵��� ������ �� �ִ� ���� (0.0�̸� ���� �̵� �Ұ���, 1.0�̸� ������ ���� ����).
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//�ȱ� �ӵ��� �ִ밪 (500�� �ӵ��� �ȱ� ����).
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	//��Ʈ�ѷ� �Է��� �ּ��� �� �ȱ� �ӵ��� 20.f�� ���� (�Ƴ��α� �Է� ����).
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	//�ȱ⿡�� ���� �� �����ϴ� ���� (2000.f�� ���ӷ� ����).
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	//���߿��� ������ �� �����ϴ� ���� (1500.f�� ���ӷ� ����).

	// ī�޶� ��(Spring Arm) ����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	/*Spring Arm ������Ʈ ���� �� RootComponent�� ����.
      Spring Arm�� ī�޶� �÷��̾� ĳ���Ϳ��� ���� �Ÿ� �����ϵ��� �ϴ� ����.*/

	CameraBoom->TargetArmLength = 400.0f; 
	//ĳ���Ϳ� ī�޶� ������ �Ÿ�(400.f ����).
	CameraBoom->bUsePawnControlRotation = true; 
	/*��Ʈ�ѷ� ȸ���� Spring Arm�� ����ǵ��� ����.
      ��, ī�޶�� ��Ʈ�ѷ��� ���� ȸ��������, ĳ���ʹ� ȸ������ ����.
      ���: ī�޶� ĳ���� �ڿ��� �������, ��Ʈ�ѷ��� ȸ�� ������ �ݿ���.*/

	// ī�޶� ������Ʈ ���� �� Spring Arm�� ����
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	/*ī�޶� �����ϰ� Spring Arm ���� ����.
       SocketName�� ����Ͽ� Spring Arm�� ���� ī�޶� ��ġ.*/

	FollowCamera->bUsePawnControlRotation = false; 
	/*ī�޶� Spring Arm�� ���� �ڵ����� �����̵��� ���� (ī�޶� ��ü�� ��Ʈ�ѷ��� ȸ���� ������� ����).
       ���: ĳ���͸� ������� 3��Ī ī�޶� ����.*/
}

void AWarriorCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// CustomMovementComponent �ʱ�ȭ (������ ���)
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