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
	/*��ȯ��: TArray<FHitResult>
                CapsuleTraceMultiForObjects()�� ����Ͽ� �浹�� ������Ʈ�� ������ �����ϴ� �迭.
      �Է°�:
              Start: ĸ�� Ʈ���̽� ���� ��ġ.
              End: ĸ�� Ʈ���̽� ���� ��ġ.
              bShowDebugShape (�⺻�� false): ����׿����� Ʈ���̽� ����� ǥ������ ����.*/


#pragma endregion

#pragma region ClimbVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> >ClimbableSurfaceTraceTypes;
	/*����: DoCapsuleTraceMultiByObject()���� � Ÿ���� ������Ʈ�� �������� �����ϴ� ����.
               EObjectTypeQuery�� �𸮾� �������� �浹 ������ ������ �� ����� �� �ִ� ������Ʈ Ÿ�� ������(Enum) �̴�.
	 �ǹ�: ĳ���Ͱ� ���� Ÿ���� ��(Static Mesh)�̳� ������(Physics Body) ���� �����ؾ� �ϴµ�,
             ClimbableSurfaceTraceTypes�� �����Ͽ� Ư�� ������Ʈ�� ������ �� �ֵ��� ���͸���.*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.f;
	/*����: CapsuleTraceMultiForObjects() �Լ����� ����ϴ� ĸ���� �������� ����.
              ��, ĳ������ ���濡�� ������ ĸ�� ũ�⸦ �����ϴ� ��.
      �ǹ�: �� ���� Ŭ���� �� ���� ������ ���� ������ �� ������, �ʹ� ũ�� ������ �ʴ� ������Ʈ�� ������ �� ����.
              �⺻�� 50.f �� ĸ�� �������� 50cm.*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight =72.f;
	/*����: CapsuleTraceMultiForObjects()���� ����ϴ� ĸ���� ���� ����.
              �� ����(HalfHeight) ���̹Ƿ� ĸ���� ��ü ���̴� 144cm�� ��.
      �ǹ�: ĳ������ �浹 ĸ�� ũ��� ����ϰ� �����Ǿ� ���� ���ɼ��� ����.
              ClimbCapsuleTraceRadius�� �Բ� �����ϸ� �� ���� ������ ������ �� ����. */


#pragma endregion

	

};

