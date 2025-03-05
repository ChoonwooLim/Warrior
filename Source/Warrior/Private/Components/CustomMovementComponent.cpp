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
		return;
    }

    // 캡슐 컴포넌트에 오버랩 이벤트 추가
    UCapsuleComponent* CapsuleComp = CharacterOwner->GetCapsuleComponent();
    if (CapsuleComp)
    {
        CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &UCustomMovementComponent::OnBeginOverlap);
        CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &UCustomMovementComponent::OnEndOverlap);
    }
}

#pragma region Debug PhySwiming

#pragma endregion

#pragma region OverridenFunctions

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

        const FRotator DirtyRotation = UpdatedComponent->GetComponentRotation();
        const FRotator CleanStandRotation = FRotator(0.f, DirtyRotation.Yaw, 0.f);
        UpdatedComponent->SetRelativeRotation(CleanStandRotation);

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

void UCustomMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
    if (IsClimbing())
    {
        PhysClimb(deltaTime, Iterations);
        
    }

    Super::PhysCustom(deltaTime, Iterations);

}

float UCustomMovementComponent::GetMaxSpeed() const
{
    if (IsClimbing())
    {
        return MaxClimbSpeed;
    }
    else
    {
        return Super::GetMaxSpeed();
    }
}

float UCustomMovementComponent::GetMaxAcceleration() const
{
    if (IsClimbing())
    {
        return MaxClimbAcceleration;
    }
    else
    {
        return Super::GetMaxAcceleration();
    }
}

void UCustomMovementComponent::PhysSwimming(float deltaTime, int32 Iterations)
{
    if (!CharacterOwner)
    {
        Debug::Print(TEXT("PhysSwimming Failed: CharacterOwner is NULL"), FColor::Red);
        return;
    }

    if (!IsSwimming())
    {
        Debug::Print(TEXT("PhysSwimming Failed: Not in Swim Mode"), FColor::Red);
        return;
    }

    if (deltaTime < MIN_TICK_TIME)
    {
        return;
    }

    RestorePreAdditiveRootMotionVelocity();

    float Depth = ImmersionDepth();
    float NetBuoyancy = Buoyancy * Depth;
    float OriginalAccelZ = Acceleration.Z;
    bool bLimitedUpAccel = false;

    if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() && (Velocity.Z > 0.33f * MaxSwimSpeed) && (NetBuoyancy != 0.f))
    {
        Velocity.Z = FMath::Max<FVector::FReal>(0.33f * MaxSwimSpeed, Velocity.Z * Depth * Depth);
    }
    else if (Depth < 0.65f)
    {
        bLimitedUpAccel = (Acceleration.Z > 0.f);
        Acceleration.Z = FMath::Min<FVector::FReal>(0.1f, Acceleration.Z);
    }

    Iterations++;
    FVector OldLocation = UpdatedComponent->GetComponentLocation();
    bJustTeleported = false;

    if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
    {
        CalcVelocity(deltaTime, 0.5f, true, GetMaxBrakingDeceleration());
        Velocity.Z += GetGravityZ() * deltaTime * (1.f - NetBuoyancy);
    }

    ApplyRootMotionToVelocity(deltaTime);

    FVector Adjusted = Velocity * deltaTime;
    FHitResult Hit(1.f);
    float remainingTime = deltaTime * Swim(Adjusted, Hit);

    if (!IsSwimming())
    {
        StartNewPhysics(remainingTime, Iterations);
        return;
    }

    // 바닥 감지를 추가하여 너무 얕은 곳에서는 수영 모드를 해제
    if (TraceSwimmableSurfaces() && !IsGroundBelow())
    {
        Debug::Print(TEXT("Swimming Mode Maintained"), FColor::Cyan);
    }
    else
    {
        Debug::Print(TEXT("Too Shallow - Exiting Swim Mode"), FColor::Red);
        SetMovementMode(MOVE_Walking);
    }
}

void UCustomMovementComponent::PhysFlying(float deltaTime, int32 Iterations)
{
          if (deltaTime < MIN_TICK_TIME)
        {
            return;
        }

        RestorePreAdditiveRootMotionVelocity();

        if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
        {
            if (bCheatFlying && Acceleration.IsZero())
            {
                Velocity = FVector::ZeroVector;
            }
            /*const float Friction = 0.5f * GetPhysicsVolume()->FluidFriction;*/
            CalcVelocity(deltaTime, 0.f, true, GetMaxBrakingDeceleration());
        }

        ApplyRootMotionToVelocity(deltaTime);

        Iterations++;
        bJustTeleported = false;

        FVector OldLocation = UpdatedComponent->GetComponentLocation();
        const FVector Adjusted = Velocity * deltaTime;
        FHitResult Hit(1.f);
        SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);

        if (Hit.Time < 1.f)
        {
            const FVector GravDir = FVector(0.f, 0.f, -1.f);
            const FVector VelDir = Velocity.GetSafeNormal();
            const float UpDown = GravDir | VelDir;

            bool bSteppedUp = false;
            if ((FMath::Abs(Hit.ImpactNormal.Z) < 0.2f) && (UpDown < 0.5f) && (UpDown > -0.2f) && CanStepUp(Hit))
            {
                float stepZ = UpdatedComponent->GetComponentLocation().Z;
                bSteppedUp = StepUp(GravDir, Adjusted * (1.f - Hit.Time), Hit);
                if (bSteppedUp)
                {
                    OldLocation.Z = UpdatedComponent->GetComponentLocation().Z + (OldLocation.Z - stepZ);
                }
            }

            if (!bSteppedUp)
            {
                //adjust and try again
                HandleImpact(Hit, deltaTime, Adjusted);
                SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
            }
        }

        if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
        {
            Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
        }
    Super::PhysFlying(deltaTime, Iterations);
}

#pragma endregion


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

void UCustomMovementComponent::PhysClimb(float deltaTime, int32 Iterations)
{
    if (deltaTime < MIN_TICK_TIME)
    {
        return;
    }

    /* Process all the climbable surfaces info */
    TraceClimbableSurfaces();

    ProcessClimbableSurfaceInfo();


    /* Check if we should stop climbing */
    if (GetShouldStopClimbing())
    {
        StopClimbing();
    }

    RestorePreAdditiveRootMotionVelocity();

    if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
    {
        //Define the max climb speed and acceleration
        CalcVelocity(deltaTime, 0.f, true, MaxBreakClimbDeceleration);
    }

    ApplyRootMotionToVelocity(deltaTime);

    FVector OldLocation = UpdatedComponent->GetComponentLocation();
    const FVector Adjusted = Velocity * deltaTime;
    FHitResult Hit(1.f);

    //Handle climb rotation
    SafeMoveUpdatedComponent(Adjusted, GetClimbRotation(deltaTime), true, Hit);

    if (Hit.Time < 1.f)
    {
        //adjust and try again
        HandleImpact(Hit, deltaTime, Adjusted);
        SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);   
    }

    if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
    {
        Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
    }

    /* Snap movement to climbable surfaces*/
    SnapMovementToClimbableSurfaces(deltaTime);

}

void UCustomMovementComponent::ProcessClimbableSurfaceInfo()
{
    CurrentClimbableSurfaceLocation = FVector::ZeroVector;
    CurrentClimbableSurfaceNormal = FVector::ZeroVector;

    if (ClimbableSurfacesTracedResults.IsEmpty()) return;
    for (const FHitResult& TracedHitResult : ClimbableSurfacesTracedResults)
    {
        CurrentClimbableSurfaceLocation += TracedHitResult.ImpactPoint;
        CurrentClimbableSurfaceNormal += TracedHitResult.ImpactNormal;
    }

    CurrentClimbableSurfaceLocation /= ClimbableSurfacesTracedResults.Num();
    CurrentClimbableSurfaceNormal = CurrentClimbableSurfaceNormal.GetSafeNormal();

}

bool UCustomMovementComponent::GetShouldStopClimbing()
{
    if (ClimbableSurfacesTracedResults.IsEmpty()) return true;

    const float DotResult = FVector::DotProduct(CurrentClimbableSurfaceNormal, FVector::UpVector);
    const float DegreeDiff = FMath::RadiansToDegrees(FMath::Acos(DotResult));

    if (DegreeDiff <=60.f)
    {
        return true;
    }

    Debug::Print(TEXT("Degree Diff: ") + FString::SanitizeFloat(DegreeDiff), FColor::Cyan, 1);

    return false;
}

FQuat UCustomMovementComponent::GetClimbRotation(float DeltaTime)
{
    const FQuat CurrentQuat = UpdatedComponent->GetComponentQuat();

    if (HasAnimRootMotion() || CurrentRootMotion.HasOverrideVelocity())
    {
        return CurrentQuat;
    }
    const FQuat TargetQuat = FRotationMatrix::MakeFromX(-CurrentClimbableSurfaceNormal).ToQuat();

    return FMath::QInterpTo(CurrentQuat, TargetQuat, DeltaTime, 5.f);

}

void UCustomMovementComponent::SnapMovementToClimbableSurfaces(float DeltaTime)
{
    const FVector ComponentForward = UpdatedComponent->GetForwardVector();
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();

    const FVector ProjectedCharacterToSurface =
        (CurrentClimbableSurfaceLocation - ComponentLocation).ProjectOnTo(ComponentForward);

    const FVector SnapVector = -CurrentClimbableSurfaceNormal * ProjectedCharacterToSurface.Length();

    UpdatedComponent->MoveComponent(
        SnapVector * DeltaTime * MaxClimbSpeed,
        UpdatedComponent->GetComponentQuat(),
        true);
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

    ClimbableSurfacesTracedResults = DoCapsuleTraceMultiByObject(Start, End, true);

	return !ClimbableSurfacesTracedResults.IsEmpty();

}

FHitResult UCustomMovementComponent::TraceFromEyeHeight(float TraceDistance, float TraceStartOffset)
{
    const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
    const FVector EyeHeightOffset = UpdatedComponent->GetUpVector() * (CharacterOwner->BaseEyeHeight + TraceStartOffset);

    const FVector Start = ComponentLocation + EyeHeightOffset;
    const FVector End = Start + UpdatedComponent->GetForwardVector() * TraceDistance;

    return DoLineTraceSingleByObject(Start, End);
}

#pragma endregion

#pragma region Swim Traces

void UCustomMovementComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherComp || !CharacterOwner) return;

    Debug::Print(TEXT("OnBeginOverlap Triggered"), FColor::Yellow);

    if (OtherComp->GetCollisionObjectType() == ECC_GameTraceChannel1)  // ECC_Water 충돌 감지
    {
        Debug::Print(TEXT("Water Overlap Detected"), FColor::Blue);

        FVector CharacterLocation = CharacterOwner->GetActorLocation();
        float CapsuleHalfHeight = CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

        // 가슴 높이 위치 (기존보다 낮게 설정)
        float ChestHeightOffset = CapsuleHalfHeight * 0.3f;  // 기존 0.4f → 0.3f로 수정
        FVector ChestLocation = CharacterLocation + FVector(0.f, 0.f, ChestHeightOffset);

        // 물 표면 감지
        FHitResult WaterHit = TraceWaterSurface(300.f);

        if (WaterHit.bBlockingHit)
        {
            float WaterSurfaceZ = WaterHit.ImpactPoint.Z;

            Debug::Print(FString::Printf(TEXT("Updated WaterSurfaceZ: %f, ChestLocationZ: %f"), WaterSurfaceZ, ChestLocation.Z), FColor::Cyan);

            // 물 표면이 가슴 높이보다 약간 낮아도 수영 모드 활성화 가능하도록 수정
            if (WaterSurfaceZ >= ChestLocation.Z - 5.0f)  // 기존보다 5cm 유연하게 적용
            {
                Debug::Print(TEXT("Water Level High Enough - Activating Swim Mode"), FColor::Green);
                ToggleSwimming(true);
            }
            else
            {
                Debug::Print(TEXT("Water Too Low - Not Activating Swim Mode"), FColor::Red);
            }
        }
        else
        {
            Debug::Print(TEXT("Water Surface Not Found"), FColor::Red);
        }
    }
}






void UCustomMovementComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherComp || !CharacterOwner) return;

    if (OtherComp->GetCollisionObjectType() == ECC_GameTraceChannel1)  // ECC_Water 충돌 감지
    {
        FVector CharacterLocation = CharacterOwner->GetActorLocation();
        float CapsuleHalfHeight = CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

        // 캐릭터의 발 위치를 기준으로 물 표면 감지
        FVector FootLocation = CharacterLocation - FVector(0.f, 0.f, CapsuleHalfHeight);

        FHitResult WaterHit = TraceWaterSurface(300.f);

        // 만약 캐릭터의 발보다 물 표면이 낮다면, 물에서 완전히 나온 것으로 판단
        if (!WaterHit.bBlockingHit || WaterHit.ImpactPoint.Z < FootLocation.Z)
        {
            Debug::Print(TEXT("Exited Water - Deactivating Swim Mode"), FColor::Yellow);
            ToggleSwimming(false);  // ✅ 직접 StopSwimming() 호출 대신 Toggle 사용
        }
        else
        {
            Debug::Print(TEXT("Still in Water - Keeping Swim Mode"), FColor::Green);
        }
    }
}


bool UCustomMovementComponent::TraceSwimmableSurfaces()
{
    const FVector Start = UpdatedComponent->GetComponentLocation();
    const FVector End = Start - FVector(0.f, 0.f, 150.f);  // 기존보다 깊이 감지

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);  // 캐릭터 자신을 제외

    bool bHit = GetWorld()->SweepSingleByObjectType(
        HitResult,
        Start,
        End,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_GameTraceChannel1),  // ECC_Water 채널 감지
        FCollisionShape::MakeCapsule(50.f, 75.f),  // 캡슐 모양으로 감지 (반지름 50, 높이 75)
        QueryParams
    );

    if (bHit)
    {
        Debug::Print(TEXT("Water Surface Detected - Entering Swim Mode"), FColor::Blue);
        return true;
    }

    Debug::Print(TEXT("No Water Detected"), FColor::Red);
    return false;
}

FHitResult UCustomMovementComponent::TraceWaterSurface(float TraceDistance)
{
    if (!CharacterOwner) return FHitResult();

    // 캐릭터의 머리 위에서부터 물 표면을 감지하도록 시작 위치를 상향 조정
    FVector Start = CharacterOwner->GetActorLocation() + FVector(0.f, 0.f, TraceDistance * 2.0f);
    FVector End = CharacterOwner->GetActorLocation() - FVector(0.f, 0.f, TraceDistance * 2);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility, // 충돌 채널 변경 가능
        QueryParams
    );

    if (bHit)
    {
        DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor::Blue, false, 2.0f, 0, 2.0f);
        Debug::Print(FString::Printf(TEXT("Updated TraceWaterSurface Hit: %f"), HitResult.ImpactPoint.Z), FColor::Green);
    }
    else
    {
        DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);
        Debug::Print(TEXT("Updated TraceWaterSurface Failed - No Hit"), FColor::Red);
    }

    return HitResult;
}






#pragma endregion

#pragma region Swim Core
   
void UCustomMovementComponent::ToggleSwimming(bool bEnableSwim)
{
    if (!CharacterOwner)
    {
        Debug::Print(TEXT("ToggleSwimming Failed: CharacterOwner is NULL"), FColor::Red);
        return;
    }

    if (bEnableSwim)
    {
        Debug::Print(TEXT("ToggleSwimming(true) called"), FColor::Yellow);

        if (CanStartSwimming())
        {
            Debug::Print(TEXT("Swim Mode Activated"), FColor::Green);
            StartSwimming();
        }
        else
        {
            Debug::Print(TEXT("Swim Mode Activation Failed: CanStartSwimming() returned false"), FColor::Red);
        }
    }
    else
    {
        Debug::Print(TEXT("ToggleSwimming(false) called"), FColor::Yellow);
        Debug::Print(TEXT("Swim Mode Deactivated"), FColor::Yellow);
        StopSwimming();
    }
}



bool UCustomMovementComponent::CanStartSwimming()
{
    if (!CharacterOwner)
    {
        Debug::Print(TEXT("Swimming Check Failed: CharacterOwner is NULL"), FColor::Red);
        return false;
    }

    if (IsFalling())
    {
        Debug::Print(TEXT("Swimming Check Failed: Character is Falling"), FColor::Red);
        return false;
    }

    if (!TraceSwimmableSurfaces())
    {
        Debug::Print(TEXT("Swimming Check Failed: No Water Surface Detected"), FColor::Red);
        return false;
    }

    Debug::Print(TEXT("Swimming Check Passed: Entering Swim Mode"), FColor::Green);
    return true;
}

void UCustomMovementComponent::StartSwimming()
{
    if (!CharacterOwner)
    {
        Debug::Print(TEXT("StartSwimming Failed: CharacterOwner is NULL"), FColor::Red);
        return;
    }

    if (IsSwimming())
    {
        Debug::Print(TEXT("Already in Swim Mode"), FColor::Red);
        return;
    }

    Debug::Print(TEXT("Swim Mode Activated"), FColor::Green);
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

#pragma region fly Core

bool UCustomMovementComponent::IsFlying() const
{
    return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Flying;
}

void UCustomMovementComponent::StartFlying()
{
    if (!CharacterOwner) return;

    if (CheckFlightCondition() && !IsFlying())
    {
        Debug::Print(TEXT("Fly Mode Activated"), FColor::Cyan);
        SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Flying);
    }
}

void UCustomMovementComponent::StopFlying()
{
    if (!CharacterOwner) return;

    if (IsFlying())
    {
        Debug::Print(TEXT("Fly Mode Deactivated"), FColor::Yellow);
        SetMovementMode(MOVE_Falling);
    }
}

#pragma endregion

