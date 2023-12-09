// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)		//범위에 들어오면 항상 탱크를 바라봄
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::HandleDestruction()	//타워가 죽었을시 레벨에서 지움
{

	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()	//레벨의 탱크를 받아오고 FireRate에 따라 Fire함수를 계속 실행함
{
	Super::BeginPlay();

	Tank = Cast <ATank> (UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()		//범위에 탱크가 들어왔으면 발사
{
	if (Tank == nullptr)
	{
		return;
	}
	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange()		//범위에 탱크가 들어왔는지 확인
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}