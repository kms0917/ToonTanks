// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "BasePawn.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATank::Jump);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &ATank::Dash);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	ManageDashCount();
	ManageJumpCount();
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;

	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), true);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);	
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation);
}

void ATank::Jump()
{
	if (JumpCount >= 1)
	{
		FVector JumpImpulse = FVector(0, 0, 700);
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(RootComponent);
		if (PrimitiveComponent)
		{
			PrimitiveComponent->AddImpulse(JumpImpulse, NAME_None, true);
		}
		JumpCount--;
	}
}

void ATank::Dash()
{
	if (DashCount >= 1)
	{
		FVector DashImpulse = FVector(600, 0, 0);
		FRotator ActorRotation = GetActorRotation();

		// 로컬 공간에서의 방향 계산
		FVector WorldDashDirection = ActorRotation.RotateVector(DashImpulse);

		// 충격을 가하는 코드
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(RootComponent);
		if (PrimitiveComponent)
		{
			PrimitiveComponent->AddImpulse(WorldDashDirection, NAME_None, true);
		}
		DashCount--;
	}
}

void ATank::AddDashCount()
{
	if (DashCount < 3)
	{
		DashCount++;
		return;
	}
	else
	{
		return;
	}
}

void ATank::AddJumpCount()
{
	if (JumpCount < 2)
	{
		JumpCount++;
		return;
	}
	else
	{
		return;
	}
}

void ATank::ManageDashCount()
{
	GetWorldTimerManager().SetTimer(DashCountTimerHandler , this, &ATank::AddDashCount, DashCountRate, true);
}

void ATank::ManageJumpCount()
{
	GetWorldTimerManager().SetTimer(JumpCountTimerHandler, this, &ATank::AddJumpCount, JumpCountRate, true);
}