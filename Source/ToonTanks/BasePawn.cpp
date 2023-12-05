// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

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

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}