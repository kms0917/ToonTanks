// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject <UCapsuleComponent>(TEXT("Capsule Ciollider"));	//캡슐 컴포넌트 생성
	RootComponent = CapsuleComp;	//캡슐 컴포넌트를 루트 컴포넌트로 할당

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));			//스태틱매시 생성
	BaseMesh->SetupAttachment(CapsuleComp);		//스태틱매시를 현재 루트 컴포넌트인 CapsuleComp에 붙힘

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));			//스태틱매시 생성
	TurretMesh->SetupAttachment(BaseMesh);		//basemesh에 붙힘

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