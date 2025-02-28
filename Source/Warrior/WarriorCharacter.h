// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "WarriorCharacter.generated.h"

class UCustomMovementComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(config=Game)
class AWarriorCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWarriorCharacter(const FObjectInitializer& ObjectInitializer);

private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UCustomMovementComponent* CustomMovementComponent;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ClimbAction;

	void OnClimbActionStarted(const FInputActionValue& Value);

	void StartFlying();

	void StopFlying();
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	/*FORCEINLINE�� �����Ϸ����� �ش� �Լ��� �ζ������� ó���϶�� �����ϴ� Ű����.
      ���� �Լ��� ª�� ������ ���(�� ��¥�� Getter)���� �Լ��� ȣ���ϴ� ���, �ڵ尡 ���� ����(inline expansion)�ǹǷ� ������ ����.
      ��, FORCEINLINE�� �����Ϸ��� ����ȭ �������� ������ �ζ��� ó������ ���� ���� �־�.
      ��, ������ ����ȭ�ϱ� ���� Getter �Լ��� �ζ������� ó���Ͽ� ���ʿ��� �Լ� ȣ�� ����� ����.*/

public:
	/*GetCameraBoom() - CameraBoom ��ȯ*/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/*����: CameraBoom (USpringArmComponent* Ÿ��)�� ��ȯ.
               CameraBoom�� ĳ���Ϳ� ī�޶� ������ �Ÿ��� �����ϴ� ������ ��.
               const �ǹ�: �Լ� ���ο��� ��� ������ �������� ������ ����.
	   ���: CameraBoom�� �ܺο��� ������ ������ �� ����.*/

	/*GetFollowCamera() - FollowCamera ��ȯ*/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/*����: FollowCamera (UCameraComponent* Ÿ��)�� ��ȯ.
               FollowCamera�� �÷��̾ ���󰡴� 3��Ī ī�޶�.
	  ���: FollowCamera�� �ܺο��� ������ ������ �� ����.*/

	/** CustomMovementComponent ��ȯ **/
	FORCEINLINE UCustomMovementComponent* GetCustomMovementComponent() const { return CustomMovementComponent; }
	/*����: CustomMovementComponent (UCustomMovementComponent* Ÿ��)�� ��ȯ.
              �⺻ UCharacterMovementComponent�� �ƴ϶�, �츮�� ���� UCustomMovementComponent�� ��ȯ�Ͽ� 
			  Ȯ��� �̵� ����� ����� �� �ֵ��� ��.
	  ���: CustomMovementComponent�� �ܺο��� �����Ͽ� �̵� ������ ������ �� ����.*/

};

