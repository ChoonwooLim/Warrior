// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


#pragma region Climb Traces

//ĸ�� Ʈ���̽�(Capsule Trace) �� �����Ͽ� ���� ���� ������Ʈ�� �浹 ���θ� �˻�
TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End, bool bShowDebugShape)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;
	
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