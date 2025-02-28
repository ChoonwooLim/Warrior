// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

private:
	
#pragma region Climb Traces

	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false );
	/*반환값: TArray<FHitResult>
                CapsuleTraceMultiForObjects()를 사용하여 충돌된 오브젝트의 정보를 저장하는 배열.
      입력값:
              Start: 캡슐 트레이스 시작 위치.
              End: 캡슐 트레이스 종료 위치.
              bShowDebugShape (기본값 false): 디버그용으로 트레이스 결과를 표시할지 여부.*/


#pragma endregion

#pragma region ClimbVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> >ClimbableSurfaceTraceTypes;
	/*역할: DoCapsuleTraceMultiByObject()에서 어떤 타입의 오브젝트를 감지할지 지정하는 변수.
               EObjectTypeQuery는 언리얼 엔진에서 충돌 감지를 수행할 때 사용할 수 있는 오브젝트 타입 열거형(Enum) 이다.
	 의미: 캐릭터가 벽을 타려면 벽(Static Mesh)이나 구조물(Physics Body) 등을 감지해야 하는데,
             ClimbableSurfaceTraceTypes을 설정하여 특정 오브젝트만 감지할 수 있도록 필터링함.*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.f;
	/*역할: CapsuleTraceMultiForObjects() 함수에서 사용하는 캡슐의 반지름을 결정.
              즉, 캐릭터의 전방에서 감지할 캡슐 크기를 조절하는 값.
      의미: 이 값이 클수록 더 넓은 범위의 벽을 감지할 수 있지만, 너무 크면 원하지 않는 오브젝트도 감지될 수 있음.
              기본값 50.f → 캡슐 반지름이 50cm.*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight =72.f;
	/*역할: CapsuleTraceMultiForObjects()에서 사용하는 캡슐의 높이 결정.
              반 높이(HalfHeight) 값이므로 캡슐의 전체 높이는 144cm가 됨.
      의미: 캐릭터의 충돌 캡슐 크기와 비슷하게 설정되어 있을 가능성이 높음.
              ClimbCapsuleTraceRadius와 함께 조정하면 벽 감지 범위를 조절할 수 있음. */


#pragma endregion

	

};

