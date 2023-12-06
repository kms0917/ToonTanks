// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include"Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject <UCapsuleComponent>(TEXT("Capsule Ciollider"));	//ĸ�� ������Ʈ ����
	RootComponent = CapsuleComp;	//ĸ�� ������Ʈ�� ��Ʈ ������Ʈ�� �Ҵ�

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));			//����ƽ�Ž� ����
	BaseMesh->SetupAttachment(CapsuleComp);		//����ƽ�Žø� ���� ��Ʈ ������Ʈ�� CapsuleComp�� ����

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));			//����ƽ�Ž� ����
	TurretMesh->SetupAttachment(BaseMesh);		//basemesh�� ����

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = ToTarget.Rotation();
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(this), 8.f));
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
}