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

	void HandleDestruction();	//탱크와 타워가 파괴될때 실행될 함수

protected:

	void RotateTurret(FVector LookAtTarget);	//탱크와 타워의 TurretMesh를 회전시킬 함수
	void Fire();	//탄을 발사하는 함수

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;	//캡슐 컴포넌트를 할당할 변수
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;			//기본 스태틱메시를 할당할 변수
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;		//기본 스태틱메시에 부착될 메시의 변수
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;	//탄이 스폰되는 위치

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;	//발사체인 Projectile클래스의 블루프린트를 만들어 메시를 설정할거기에 Projectile클래스의 자식 클래스형 변수를 만듦

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticles;		//폰이 죽을때의 이펙트

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* DeathSound;		//폰이 죽을때의 소리

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
 	TSubclassOf<class UCameraShakeBase> DeathCameraShake;		//폰이 죽을때의 카메라 움직임
};