// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "CustomMovementComponent.generated.h"


UENUM()
namespace ECustomMovementMode
{
    enum Type
    {
		MOVE_Climb UMETA(DisplayName = "Climb Mode"),
		MOVE_Flying UMETA(DisplayName = "Fly Mode"),
		MOVE_Swimming UMETA(DisplayName = "Swim Mode")
    };
}


/**
 * 
 */

UCLASS()
class WARRIOR_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

#pragma region OverridenFunctions

protected:

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
    virtual void PhysCustom(float deltaTime, int32 Iterations) override;
    virtual void PhysSwimming(float deltaTime, int32 Iterations);
    virtual void PhysFlying(float deltaTime, int32 Iterations);

    virtual float GetMaxSpeed() const override;
    virtual float GetMaxAcceleration() const override;

#pragma endregion

    
private:

	void SetUpdatedComponent(USceneComponent* NewUpdatedComponent);
    /*USceneComponent* 타입의 새로운 컴포넌트를 입력받아 이동 컴포넌트로 설정하는 함수.
      UpdatedComponent는 UCharacterMovementComponent 또는 UCustomMovementComponent에서 캐릭터의 이동을 처리하는 핵심 컴포넌트.
      예를 들어, RootComponent 또는 CapsuleComponent를 이동 대상 컴포넌트로 지정할 수 있음.
      즉, "이동해야 할 대상 컴포넌트를 설정하는 역할"을 함.*/


private:

#pragma region Climb Traces

	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false, bool bDrawPersistantShapes = false);
	/*반환값: TArray<FHitResult>
                CapsuleTraceMultiForObjects()를 사용하여 충돌된 오브젝트의 정보를 저장하는 배열.
      입력값:
              Start: 캡슐 트레이스 시작 위치.
              End: 캡슐 트레이스 종료 위치.
              bShowDebugShape (기본값 false): 디버그용으로 트레이스 결과를 표시할지 여부.*/

    FHitResult DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape = false, bool bDrawPersistantShapes = false);


#pragma endregion

#pragma region ClimbCore

    bool TraceClimbableSurfaces();

    FHitResult TraceFromEyeHeight(float TraceDistance, float TraceStartOffset = 0.f);

	bool CanStartClimbing();

	void StartClimbing();

	void StopClimbing();

    void PhysClimb(float deltaTime, int32 Iterations);

    void ProcessClimbableSurfaceInfo();

    bool GetShouldStopClimbing();

    FQuat GetClimbRotation(float DeltaTime);

    void SnapMovementToClimbableSurfaces(float DeltaTime);

#pragma endregion

#pragma region ClimbCoreVariables

	TArray<FHitResult> ClimbableSurfacesTracedResults;

    FVector CurrentClimbableSurfaceLocation;

    FVector CurrentClimbableSurfaceNormal;

#pragma endregion

#pragma region ClimbBPVariables

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
    float MaxBreakClimbDeceleration = 400.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
    float MaxClimbSpeed = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
    float MaxClimbAcceleration= 300.f;


#pragma endregion

public:
	void ToggleClimbing(bool bEnableClimb);
	/*입력값: bEnableClimb
				true: 캐릭터가 벽을 탈 수 있는 상태로 전환.
				false: 캐릭터가 벽을 탈 수 없는 상태로 전환.
	  역할: 캐릭터의 벽 타기 상태를 전환하는 함수.
	  의미: bEnableClimb이 true이면 캐릭터가 벽을 탈 수 있는 상태로 전환되어 벽을 탈 수 있게 됨.
			  bEnableClimb이 false이면 캐릭터가 벽을 탈 수 없는 상태로 전환되어 벽을 탈 수 없게 됨.*/
    bool IsClimbing() const;

    FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNormal; }


#pragma region Swim Traces

public:
    bool TraceSwimmableSurfaces();
    FHitResult TraceWaterSurface(float TraceDistance);

    

#pragma endregion

#pragma region Swim Core

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
    void ToggleSwimming(bool bEnableSwim);
    bool CanStartSwimming();
    void StartSwimming();
    void StopSwimming();
    bool IsSwimming() const override;

    private:
		bool bHasEnteredWater = false; // 물에 들어갔는지 여부를 저장하는 변수.

   
#pragma endregion

#pragma region Swim Core Variables

private:
	TArray<FHitResult> SwimmableSurfacesTracedResults;

#pragma endregion




#pragma region Fly Traces

public:

    UFUNCTION(BlueprintCallable, Category = "Character Movement: Flying")
    bool CheckFlightCondition();

    UFUNCTION(BlueprintCallable, Category = "Character Movement: Flying")
    bool IsCeilingAbove();

    UFUNCTION(BlueprintCallable, Category = "Character Movement: Flying")
    bool IsGroundBelow();

    UFUNCTION(BlueprintCallable, Category = "Character Movement: Flying")
    bool CheckObstacleAhead();

#pragma endregion

#pragma region Fly Core

    public:
        bool IsFlying() const override;

        void StartFlying();

        void StopFlying();


#pragma endregion

#pragma region Fly Variables

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Flying", meta = (AllowPrivateAccess = "true"))
    float FlightTraceDistance = 500.f;  // 비행 가능 여부를 체크할 거리

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Flying", meta = (AllowPrivateAccess = "true"))
    float CeilingTraceDistance = 200.f; // 천장 감지 거리

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Flying", meta = (AllowPrivateAccess = "true"))
    float GroundTraceDistance = 1000.f; // 지면 감지 거리

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Flying", meta = (AllowPrivateAccess = "true"))
    float ObstacleTraceDistance = 300.f; // 장애물 감지 거리

#pragma endregion


};

