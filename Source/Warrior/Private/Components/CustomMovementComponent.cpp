// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "Warrior/WarriorCharacter.h"
#include "Components/CapsuleComponent.h"

#include "Warrior/DebugHelper.h"



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

    /*TraceClimbableSurfaces();
       TraceFromEyeHeight(100.f); */

}

void UCustomMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
    if (IsClimbing())
    {
        bOrientRotationToMovement = false;
		CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(48.f);
	}

    if (PreviousMovementMode == MOVE_Custom && PreviousCustomMode == ECustomMovementMode::MOVE_Climb)
    {
        bOrientRotationToMovement = true;
        CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);

		StopMovementImmediately();
    }

    if (IsSwimming())
    {
        bOrientRotationToMovement = false;
        CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(60.f); // 물 속에서는 충돌 크기 감소
    }

    if (PreviousMovementMode == MOVE_Custom && PreviousCustomMode == ECustomMovementMode::MOVE_Swimming)
    {
        bOrientRotationToMovement = true;
        CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(96.f);

        StopMovementImmediately();
    }

	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
	
}


#pragma region Climb Traces

//캡슐 트레이스(Capsule Trace) 를 실행하여 여러 개의 오브젝트와 충돌 여부를 검사
TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape, bool bDrawPersistantShapes)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;

    EDrawDebugTrace::Type DebugTraceType = EDrawDebugTrace::None;

    if (bShowDebugShape)
    {
        DebugTraceType = EDrawDebugTrace::ForOneFrame;

        if (bDrawPersistantShapes)
        {
            DebugTraceType = EDrawDebugTrace::Persistent;
        }
    }

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
        DebugTraceType,
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

FHitResult UCustomMovementComponent::DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool bShowDebugShape, bool bDrawPersistantShapes)
{
    FHitResult OutHit;

	EDrawDebugTrace::Type DebugTraceType = EDrawDebugTrace::None;

    if (bShowDebugShape)
    {
		DebugTraceType = EDrawDebugTrace::ForOneFrame;

        if (bDrawPersistantShapes)
        {
            DebugTraceType = EDrawDebugTrace::Persistent;
        }

    }

    UKismetSystemLibrary::LineTraceSingleForObjects(
        this,
        Start,
        End,
        ClimbableSurfaceTraceTypes,
        false,
        TArray<AActor*>(),
        DebugTraceType,
        OutHit,
        false
    );

    return OutHit;
}

#pragma endregion

#pragma region ClimbCore

void UCustomMovementComponent::ToggleClimbing(bool bEnableClimb)
{
	if (!CharacterOwner) return;
    if (bEnableClimb)
    {
        if (CanStartClimbing())
        {
            //Enter the climb state
            Debug::Print(TEXT("Climb Mode Activated"));
            StartClimbing();
        }
        else
        {
            //Failed to climb
            Debug::Print(TEXT("Climb Mode Failed"));
        }
    }
	else
	{
		// Stop climbing
        StopClimbing();
       
	}
}

bool UCustomMovementComponent::CanStartClimbing()
{
	if (IsFalling()) return false;
    if (!TraceClimbableSurfaces()) return false;
	if (!TraceFromEyeHeight(100.f).bBlockingHit) return false;

	return true;
   
}

void UCustomMovementComponent::StartClimbing()
{
	SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Climb);
}

void UCustomMovementComponent::StopClimbing()
{
	SetMovementMode(MOVE_Falling);
}

bool UCustomMovementComponent::IsClimbing() const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Climb;
}


//Trace for climbable surfaces, return ture if there are indeed valid surfaces, false otherwise.
bool UCustomMovementComponent::TraceClimbableSurfaces()
{
    const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f;
    const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector();

    ClimbableSurfacesTracedResults = DoCapsuleTraceMultiByObject(Start, End, true,true);

	return !ClimbableSurfacesTracedResults.IsEmpty();

}

FHitResult UCustomMovementComponent::TraceFromEyeHeight(float TraceDistance, float TraceStartOffset)
{
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
    const FVector EyeHeightOffset = UpdatedComponent->GetUpVector() * (CharacterOwner->BaseEyeHeight + TraceStartOffset);

    const FVector Start = ComponentLocation + EyeHeightOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector() * TraceDistance;

    return DoLineTraceSingleByObject(Start, End, true,true);
}

#pragma endregion

#pragma region Swim Traces

bool UCustomMovementComponent::TraceSwimmableSurfaces()
{
    const FVector StartOffset = FVector(0.f, 0.f, -30.f); // 약간 아래로 탐색
    const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
    const FVector End = Start - FVector(0.f, 0.f, 50.f); // 아래 방향으로 탐색

    SwimmableSurfacesTracedResults = DoCapsuleTraceMultiByObject(Start, End, true, true);

    return !SwimmableSurfacesTracedResults.IsEmpty();
}

FHitResult UCustomMovementComponent::TraceWaterSurface(float TraceDistance, float TraceStartOffset)
{
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
    const FVector EyeHeightOffset = FVector(0.f, 0.f, CharacterOwner->BaseEyeHeight + TraceStartOffset);

    const FVector Start = ComponentLocation + EyeHeightOffset;
    const FVector End = Start - FVector(0.f, 0.f, TraceDistance);

    return DoLineTraceSingleByObject(Start, End, true, true);
}


#pragma endregion

#pragma region Swim Core
   
void UCustomMovementComponent::ToggleSwimming(bool bEnableSwim)
{
    if (!CharacterOwner) return;

    if (bEnableSwim)
    {
        if (CanStartSwimming())
        {
            Debug::Print(TEXT("Swim Mode Activated"));
            StartSwimming();
        }
        else
        {
            Debug::Print(TEXT("Swim Mode Failed"));
        }
    }
    else
    {
        StopSwimming();
    }
}

bool UCustomMovementComponent::CanStartSwimming()
{
    if (IsFalling()) return false;
    if (!TraceSwimmableSurfaces()) return false;
    if (!TraceWaterSurface(100.f).bBlockingHit) return false;

    return true;
}

void UCustomMovementComponent::StartSwimming()
{
    SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Swimming);
}

void UCustomMovementComponent::StopSwimming()
{
    SetMovementMode(MOVE_Walking);
}

bool UCustomMovementComponent::IsSwimming() const
{
    return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Swimming;
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

