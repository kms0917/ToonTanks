// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();	//��ũ�� Ÿ���� �ı��ɶ� ����� �Լ�

protected:

	void RotateTurret(FVector LookAtTarget);	//��ũ�� Ÿ���� TurretMesh�� ȸ����ų �Լ�
	void Fire();	//ź�� �߻��ϴ� �Լ�

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;	//ĸ�� ������Ʈ�� �Ҵ��� ����
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;			//�⺻ ����ƽ�޽ø� �Ҵ��� ����
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;		//�⺻ ����ƽ�޽ÿ� ������ �޽��� ����
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;	//ź�� �����Ǵ� ��ġ

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;	//�߻�ü�� ProjectileŬ������ �������Ʈ�� ����� �޽ø� �����Ұű⿡ ProjectileŬ������ �ڽ� Ŭ������ ������ ����

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticles;		//���� �������� ����Ʈ

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* DeathSound;		//���� �������� �Ҹ�

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
 	TSubclassOf<class UCameraShakeBase> DeathCameraShake;		//���� �������� ī�޶� ������
};