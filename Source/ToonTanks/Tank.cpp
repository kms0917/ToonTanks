// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "BasePawn.h"

ATank::ATank()	//카메라 부착
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)	//키 바인딩
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATank::Jump);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &ATank::Dash);
}

void ATank::BeginPlay()		//Dash와 Jump 횟수를 관리할 함수들 실행
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

	ManageDashCount();
	ManageJumpCount();
}

void ATank::Tick(float DeltaTime)	//매 틱마다 커서 위치로 TurretMesh를 돌림
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()		//Tank가 파괴될때 게임에서 Tank가 안보이게 한 후 입력을 받지 않게함
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::Move(float Value)	//앞뒤 움직임 구현
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);	
}

void ATank::Turn(float Value)	//좌위 회전 구현
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation);
}

void ATank::Jump()	//점프 구현
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

void ATank::Dash()	//대쉬 구현
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

void ATank::AddDashCount()	//Dash 횟수 추가하는 함수
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

void ATank::AddJumpCount()	//Jump횟수 추가하는 함수
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

void ATank::ManageDashCount()	//Dash 횟수를 DashCountRate의 값에 따라 주기적으로 회복시킴
{
	GetWorldTimerManager().SetTimer(DashCountTimerHandler , this, &ATank::AddDashCount, DashCountRate, true);
}

void ATank::ManageJumpCount()	//Jump 횟수를 JumpCountRate의 값에 따라 주기적으로 회복시킴
{
	GetWorldTimerManager().SetTimer(JumpCountTimerHandler, this, &ATank::AddJumpCount, JumpCountRate, true);
}