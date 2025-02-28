// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"


void UCustomMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
    Super::SetUpdatedComponent(NewUpdatedComponent);

    // GetOwner()�� ���� �����ϰ� CharacterOwner �ʱ�ȭ
    CharacterOwner = Cast<ACharacter>(GetOwner());

    if (!CharacterOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("CharacterOwner is NULL in CustomMovementComponent!"));
    }
}


#pragma region Climb Traces

//ĸ�� Ʈ���̽�(Capsule Trace) �� �����Ͽ� ���� ���� ������Ʈ�� �浹 ���θ� �˻�
TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;

    if (!CharacterOwner) return OutCapsuleTraceHitResults; // ��� �ڵ� �߰�
	
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(
        this, //���� CustomMovementComponent ��ü�� ��Ÿ��.
		Start, //Ʈ���̽��� ���� ����
		End, //Ʈ���̽��� �� ����. ���� ĳ������ ���� ��ġ(Start)���� �̵� ����(End)�� �����Ͽ� ���� ������.
		ClimbCapsuleTraceRadius, //ĸ�� Ʈ���̽��� ������
		ClimbCapsuleTraceHalfHeight, //ĸ�� Ʈ���̽��� �ݳ���. ��, Ʈ���̽� ���� ũ�⸦ �ǹ���.
		ClimbableSurfaceTraceTypes, //������ ������Ʈ�� ����(Object Type).
		/*���� ���, ECC_WorldStatic (������ ����)�̳� ECC_PhysicsBody (���� ������Ʈ) ���� Ÿ���� ������ �� ����.
           �� ������ ���� Ư�� ǥ�鸸 �����ϵ��� ���͸��� �� ����.*/

		false, //�ڱ� �ڽ�(ĳ����)�� �������� �������� ����. false�� �����Ǿ� �־�, �ڱ� �ڽ��� ���� ������� ������ ���� ����.
		TArray<AActor*>(), //Ʈ���̽����� ������ ���� ����Ʈ. �⺻������ �� �迭�̹Ƿ�, ��� ���͸� ������� Ʈ���̽���.
		bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		/*����� Ʈ���̽� �ɼ�
           bShowDebugShape == true�̸� EDrawDebugTrace::ForOneFrame���� ���� �� 1������ ���� ����� ���� ǥ��.
           bShowDebugShape == false�̸� EDrawDebugTrace::None���� ���� �� ����� ���� ��Ȱ��ȭ.*/

		OutCapsuleTraceHitResults, //�浹 ����� ������ �迭. Ʈ���̽��� ������ ��� �浹 ������ ���⿡ ������.
		false //���� ��Ƽ����(Physical Material) ������ ��ȯ���� ����.  false�� �����Ǿ� �־� ���� ��Ƽ���� ������ ������.
	);

	return OutCapsuleTraceHitResults; //������ ��� �浹 ������ ���� TArray<FHitResult>�� ��ȯ.
}


#pragma endregion

#pragma region Swim Traces

bool UCustomMovementComponent::CheckSwimmingCondition()
{
    if (!CharacterOwner)
    {
        return false; // ĳ���Ͱ� ������ ���� üũ �Ұ���
    }

    FHitResult HitResult;
    FVector Start = CharacterOwner->GetActorLocation();
    FVector End = Start - FVector(0.f, 0.f, SwimTraceDepth);

    bool bHit = GetWorld()->SweepSingleByObjectType(
        HitResult,
        Start,
        End,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
        FCollisionShape::MakeSphere(SwimTraceRadius),
        FCollisionQueryParams(NAME_None, false, CharacterOwner)
    );

    if (bHit)
    {
        // �� ���� üũ (�ʹ� ���� �������� ���� �Ұ�)
        float WaterDepth = Start.Z - HitResult.ImpactPoint.Z;
        if (WaterDepth < 30.f) return false;

        // ActorHasTag �Ǵ� SurfaceType���� Ȯ�� ����
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->ActorHasTag("Water"))
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
        return false; // õ���� �ʹ� ������ ���� �Ұ���
    }

    if (CheckObstacleAhead())
    {
        UE_LOG(LogTemp, Warning, TEXT("Flight Blocked: Obstacle ahead!"));
        return false; // �տ� ��ֹ��� ������ ���� �Ұ���
    }

    if (!IsGroundBelow())
    {
        UE_LOG(LogTemp, Warning, TEXT("Flight Blocked: No ground detected!"));
        return false; // ������ �������� ������ ���� �Ұ���
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

    return bHit; // õ���� �����Ǹ� true ��ȯ
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

    return bHit; // ������ �����Ǹ� true ��ȯ
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

    return bHit; // ��ֹ��� �����Ǹ� true ��ȯ
}




#pragma endregion

