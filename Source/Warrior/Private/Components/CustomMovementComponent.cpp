// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Warrior/WarriorCharacter.h"


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

    
    TraceClimbableSurfaces();
    TraceFromEyeHeight(100.f);
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

#pragma region Swim Traces

bool UCustomMovementComponent::CheckSwimmingCondition()
{
    if (!CharacterOwner) return false; // 캐릭터가 없으면 체크 불가능

    FHitResult HitResult;
    FVector Start = CharacterOwner->GetActorLocation();
    FVector End = Start - FVector(0.f, 0.f, SwimTraceDepth); // 아래로 탐색

    // 물체 감지: ECC_Water (새로운 Collision Channel 설정 필요)
    bool bHit = GetWorld()->SweepSingleByObjectType(
        HitResult,
        Start,
        End,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),  // 물 전용 감지 채널
        /*ECC_GameTraceChannel1 → 위에서 ECC_Water를 추가한 경우, 게임 내 Object Channel 번호로 등록됨.
           (ECC_GameTraceChannel1, ECC_GameTraceChannel2 등 번호는 설정에 따라 다를 수 있음.)*/

        FCollisionShape::MakeSphere(SwimTraceRadius),
        FCollisionQueryParams(NAME_None, false, CharacterOwner)
    );

    if (bHit)
    {
        // 1️⃣ 물의 깊이 체크 (너무 얕은 곳에서는 수영 불가)
        float WaterDepth = Start.Z - HitResult.ImpactPoint.Z;
        if (WaterDepth < 50.f) return false;  // 최소 수영 가능 깊이 설정

        // 2️⃣ 감지된 액터가 'Water' 태그를 가졌는지 확인
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->ActorHasTag("Water"))
        {
            return true;
        }

        // 3️⃣ 감지된 표면 머티리얼이 물인지 확인 (추가 보완)
        UPhysicalMaterial* PhysMat = HitResult.PhysMaterial.Get();
        if (PhysMat && PhysMat->SurfaceType == EPhysicalSurface::SurfaceType1) // SurfaceType_Water
        {
            return true;
        }
    }

    return false;
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

