// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)		//������ ������ �׻� ��ũ�� �ٶ�
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::HandleDestruction()	//Ÿ���� �׾����� �������� ����
{

	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()	//������ ��ũ�� �޾ƿ��� FireRate�� ���� Fire�Լ��� ��� ������
{
	Super::BeginPlay();

	Tank = Cast <ATank> (UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()		//������ ��ũ�� �������� �߻�
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

bool ATower::InFireRange()		//������ ��ũ�� ���Դ��� Ȯ��
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