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

	/*FORCEINLINE은 컴파일러에게 해당 함수를 인라인으로 처리하라고 강제하는 키워드.
      보통 함수가 짧고 간단한 경우(한 줄짜리 Getter)에는 함수를 호출하는 대신, 코드가 직접 삽입(inline expansion)되므로 성능이 향상됨.
      단, FORCEINLINE은 컴파일러의 최적화 과정에서 무조건 인라인 처리되지 않을 수도 있어.
      즉, 성능을 최적화하기 위해 Getter 함수를 인라인으로 처리하여 불필요한 함수 호출 비용을 줄임.*/

public:
	/*GetCameraBoom() - CameraBoom 반환*/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/*역할: CameraBoom (USpringArmComponent* 타입)을 반환.
               CameraBoom은 캐릭터와 카메라 사이의 거리를 조정하는 역할을 함.
               const 의미: 함수 내부에서 멤버 변수를 변경하지 않음을 보장.
	   결과: CameraBoom을 외부에서 가져와 조작할 수 있음.*/

	/*GetFollowCamera() - FollowCamera 반환*/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/*역할: FollowCamera (UCameraComponent* 타입)를 반환.
               FollowCamera는 플레이어를 따라가는 3인칭 카메라.
	  결과: FollowCamera를 외부에서 가져와 설정할 수 있음.*/

	/** CustomMovementComponent 반환 **/
	FORCEINLINE UCustomMovementComponent* GetCustomMovementComponent() const { return CustomMovementComponent; }
	/*역할: CustomMovementComponent (UCustomMovementComponent* 타입)를 반환.
              기본 UCharacterMovementComponent가 아니라, 우리가 만든 UCustomMovementComponent를 반환하여 
			  확장된 이동 기능을 사용할 수 있도록 함.
	  결과: CustomMovementComponent를 외부에서 접근하여 이동 로직을 조작할 수 있음.*/

};

