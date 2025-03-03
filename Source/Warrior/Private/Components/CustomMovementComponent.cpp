// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Warrior/WarriorCharacter.h"
#include "Components/CapsuleComponent.h"


void UCustomMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
    Super::SetUpdatedComponent(NewUpdatedComponent);

    // GetOwner()를 통해 안전하게 CharacterOwner 초기화
    CharacterOwner = Cast<ACharacter>(GetOwner());

    if (!CharacterOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterOwner is NULL in CustomMovementComponent!"));
    }
}

void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // 등반 감지 (기존 기능)
    TraceClimbableSurfaces();
    TraceFromEyeHeight(100.f);


    // 수영 가능 여부 체크 후 자동 전환
    if (CheckSwimmingCondition())
    {
        if (MovementMode != MOVE_Swimming) // 이미 수영 중이 아니면 변경
        {
            SetMovementMode(MOVE_Swimming);
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Automatic Swimming Mode Activated"));
        }
    }
    else
    {
        if (MovementMode == MOVE_Swimming) // 물을 벗어나면 걷기 모드로 변경
        {
            SetMovementMode(MOVE_Walking);
            GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Automatic Swimming Mode Deactivated"));
        }
    }
}


#pragma region Climb Traces

//캡슐 트레이스(Capsule Trace) 를 실행하여 여러 개의 오브젝트와 충돌 여부를 검사
TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;

    if (!CharacterOwner) return OutCapsuleTraceHitResults; // 방어 코드 추가
	
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(
        this, //현재 CustomMovementComponent 객체를 나타냄.
		Start, //트레이스의 시작 지점
		End, //트레이스의 끝 지점. 보통 캐릭터의 현재 위치(Start)에서 이동 방향(End)을 설정하여 벽을 감지함.
		ClimbCapsuleTraceRadius, //캡슐 트레이스의 반지름
		ClimbCapsuleTraceHalfHeight, //캡슐 트레이스의 반높이. 즉, 트레이스 범위 크기를 의미함.
		ClimbableSurfaceTraceTypes, //감지할 오브젝트의 유형(Object Type).
		/*예를 들어, ECC_WorldStatic (고정된 지형)이나 ECC_PhysicsBody (물리 오브젝트) 같은 타입을 설정할 수 있음.
           이 변수를 통해 특정 표면만 감지하도록 필터링할 수 있음.*/

		false, //자기 자신(캐릭터)을 감지에서 제외할지 여부. false로 설정되어 있어, 자기 자신을 감지 대상으로 포함할 수도 있음.
		TArray<AActor*>(), //트레이스에서 무시할 액터 리스트. 기본적으로 빈 배열이므로, 모든 액터를 대상으로 트레이스함.
		bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		/*디버그 트레이스 옵션
           bShowDebugShape == true이면 EDrawDebugTrace::ForOneFrame으로 설정 → 1프레임 동안 디버그 라인 표시.
           bShowDebugShape == false이면 EDrawDebugTrace::None으로 설정 → 디버그 라인 비활성화.*/
          
		OutCapsuleTraceHitResults, //충돌 결과를 저장할 배열. 트레이스가 감지한 모든 충돌 정보를 여기에 저장함.
		false //물리 머티리얼(Physical Material) 정보를 반환할지 여부.  false로 설정되어 있어 물리 머티리얼 정보를 무시함.
	);

	/* 강제로 라인을 그려 디버깅하기
        DrawDebugLine(GetWorld(),Start,End,FColor::Red,false, 2.0f, 0, 2.0f);*/

	return OutCapsuleTraceHitResults; //감지된 모든 충돌 정보를 담은 TArray<FHitResult>를 반환.
}

FHitResult UCustomMovementComponent::DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape)
{
    FHitResult OutHit;

    UKismetSystemLibrary::LineTraceSingleForObjects(
        this,
        Start,
        End,
        ClimbableSurfaceTraceTypes,
        false,
        TArray<AActor*>(),
        bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
        OutHit,
        false
    );

    return OutHit;
}

#pragma endregion

#pragma region ClimbCore

void UCustomMovementComponent::TraceClimbableSurfaces()
{
    const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f;
    const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector();

    DoCapsuleTraceMultiByObject(Start, End, true);
}

void UCustomMovementComponent::TraceFromEyeHeight(float TraceDistance, float TraceStartOffset)
{
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
    const FVector EyeHeightOffset = UpdatedComponent->GetUpVector() * (CharacterOwner->BaseEyeHeight + TraceStartOffset);

    const FVector Start = ComponentLocation + EyeHeightOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector() * TraceDistance;

    DoLineTraceSingleByObject(Start, End, true);
}

#pragma endregion

bool UCustomMovementComponent::CheckSwimmingCondition()
{
    ACharacter* Character = Cast<ACharacter>(CharacterOwner);
    if (!Character || !Character->GetCapsuleComponent())
    {
        UE_LOG(LogTemp, Error, TEXT("CheckSwimmingCondition: CharacterOwner is not valid!"));
        return false;
    }

    // 🎯 허리 위치 계산 (허리는 캡슐 높이의 약 40% 지점)
    FVector WaistOffset = FVector(0.f, 0.f, Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 0.4f);
    FVector WaistLocation = Character->GetActorLocation() - WaistOffset; // 허리 위치

    // 🎯 물 표면 감지 (허리 아래로 트레이스)
    FVector WaterTraceStart = WaistLocation;
    FVector WaterTraceEnd = WaterTraceStart - FVector(0.f, 0.f, SwimTraceDepth);

    FHitResult WaterHitResult;
    bool bWaterHit = GetWorld()->SweepSingleByObjectType(
        WaterHitResult,
        WaterTraceStart,
        WaterTraceEnd,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1), // 물 감지용 채널
        FCollisionShape::MakeSphere(SwimTraceRadius),
        FCollisionQueryParams(NAME_None, false, Character)
    );

    // 감지된 물 표면의 절대 높이 (물 감지가 실패하면 기본값을 설정)
    float WaterSurfaceZ = bWaterHit ? WaterHitResult.Location.Z : (Character->GetActorLocation().Z - 200.f);

    // 🎯 물 높이와 허리 높이 비교하여 WaterDepth 계산
    float WaterDepth = WaterSurfaceZ - WaistLocation.Z;

    UE_LOG(LogTemp, Warning, TEXT("CheckSwimmingCondition: WaterDepth = %f, WaterSurfaceZ = %f, WaistZ = %f"), WaterDepth, WaterSurfaceZ, WaistLocation.Z);

    // 🎯 물 높이가 허리보다 높으면 수영 모드
    if (WaterSurfaceZ > WaistLocation.Z)
    {
        if (MovementMode != MOVE_Swimming)
        {
            SetMovementMode(MOVE_Swimming);
            UE_LOG(LogTemp, Warning, TEXT("Swimming Mode Activated (WaterDepth: %f)"), WaterDepth);
        }
        return true;
    }

    // 🎯 물 높이가 허리보다 낮으면 걷기 모드
    if (MovementMode == MOVE_Swimming)
    {
        SetMovementMode(MOVE_Walking);
        UE_LOG(LogTemp, Warning, TEXT("Walking Mode Activated (WaterDepth: %f)"), WaterDepth);
    }

    return false;
}


void UCustomMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
    if (MovementMode == MOVE_Swimming)
    {
        PerformSwimMovement(DeltaTime);
    }
}

void UCustomMovementComponent::PerformSwimMovement(float DeltaTime)
{
    if (!CharacterOwner) return;

    // 🎯 입력 벡터 가져오기
    FVector InputVector = ConsumeInputVector();
    FVector SwimVelocity = InputVector * SwimSpeed; // 수영 속도 적용

    // 🎯 중력 감소 효과 적용 (부드러운 떠오름)
    float SwimGravityScale = 0.2f; // 🎯 지역 변수 이름 변경 (GravityScale → SwimGravityScale)
    SwimVelocity.Z += SwimGravityScale * GetGravityZ() * DeltaTime;

    // 🎯 점프(부상) 및 하강 처리
    if (CharacterOwner->GetCharacterMovement()->IsFalling())
    {
        SwimVelocity.Z += 300.f * DeltaTime; // 캐릭터가 상승할 때 약간의 부력 추가
    }
    else if (InputVector.Z < 0)
    {
        SwimVelocity.Z -= 200.f * DeltaTime; // 캐릭터가 하강할 때 추가 하강 처리
    }

    // 🎯 부드러운 이동 적용 (보간 처리)
    Velocity = FMath::VInterpTo(Velocity, SwimVelocity, DeltaTime, 5.0f);

    // 🎯 실제 위치 업데이트
    FVector NewLocation = CharacterOwner->GetActorLocation() + (Velocity * DeltaTime);
    CharacterOwner->SetActorLocation(NewLocation, true);
}



#pragma endregion

#pragma region Flight Traces

bool UCustomMovementComponent::CheckFlightCondition()
{
    if (!CharacterOwner) return false;

    if (IsCeilingAbove())
    {
        UE_LOG(LogTemp, Warning, TEXT("Flight Blocked: Ceiling too close!"));
        return false; // 천장이 너무 가까우면 비행 불가능
    }

    if (CheckObstacleAhead())
    {
        UE_LOG(LogTemp, Warning, TEXT("Flight Blocked: Obstacle ahead!"));
        return false; // 앞에 장애물이 있으면 비행 불가능
    }

    if (!IsGroundBelow())
    {
        UE_LOG(LogTemp, Warning, TEXT("Flight Blocked: No ground detected!"));
        return false; // 지면이 감지되지 않으면 비행 불가능
    }
    return true;
}

bool UCustomMovementComponent::IsCeilingAbove()
{
    if (!CharacterOwner) return false;

    FHitResult HitResult;
    FVector Start = CharacterOwner->GetActorLocation();
    FVector End = Start + FVector(0.f, 0.f, CeilingTraceDistance);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        FCollisionQueryParams(NAME_None, false, CharacterOwner)
    );

    return bHit; // 천장이 감지되면 true 반환
}

bool UCustomMovementComponent::IsGroundBelow()
{
    if (!CharacterOwner) return false;

    FHitResult HitResult;
    FVector Start = CharacterOwner->GetActorLocation();
    FVector End = Start - FVector(0.f, 0.f, GroundTraceDistance);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        FCollisionQueryParams(NAME_None, false, CharacterOwner)
    );

    return bHit; // 지면이 감지되면 true 반환
}

bool UCustomMovementComponent::CheckObstacleAhead()
{
    if (!CharacterOwner) return false;

    FHitResult HitResult;
    FVector Start = CharacterOwner->GetActorLocation();
    FVector End = Start + CharacterOwner->GetActorForwardVector() * ObstacleTraceDistance;

    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        Start,
        End,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeCapsule(50.f, 100.f),
        FCollisionQueryParams(NAME_None, false, CharacterOwner)
    );

    return bHit; // 장애물이 감지되면 true 반환
}




#pragma endregion

