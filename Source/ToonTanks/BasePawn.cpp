// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include"Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;	//ƽ�� �����ϰ� ��
	
	CapsuleComp = CreateDefaultSubobject <UCapsuleComponent>(TEXT("Capsule Ciollider"));	//ĸ�� ������Ʈ ����
	RootComponent = CapsuleComp;	//ĸ�� ������Ʈ�� ��Ʈ ������Ʈ�� �Ҵ�

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));			//����ƽ�Ž� ����
	BaseMesh->SetupAttachment(CapsuleComp);		//����ƽ�Žø� ���� ��Ʈ ������Ʈ�� CapsuleComp�� ����

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));			//����ƽ�Ž� ����
	TurretMesh->SetupAttachment(BaseMesh);		//basemesh�� ����

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));	//�߻�ü�� ������ ��ġ ���� �� ����
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());	//���� ��ġ�� DeathParticles ���
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());	//���� ��ġ�� DeathSound ���
	}
	if (DeathCameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShake);	//������ ī�޶� ����ũ ���
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)		//�Է����� ���� ��ġ�� TurretMesh�� ������ �Լ�
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = ToTarget.Rotation();
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 8.f));
}

void ABasePawn::Fire()		//�߻�ü�� �����ϴ� �Լ�
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}