// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;	//�߻�ü�� �̵��� ���� ���� 

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpurse, const FHitResult& Hit);	//�߻�ü�� �������� �����ų �Լ�

	UPROPERTY(EditAnyWhere)
	float Damage = 10.f;	//�߻�ü�� ������

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;	//�߻�ü�� �������� ����Ʈ

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;	//�߻�ü�� ������ ����Ʈ

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;	//�߻�ü �߻� �Ҹ�

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;		//�߻�ü�� �������� �Ҹ�

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;	//�߻�ü�� ������ ī�޶� ����ũ�� �����Ű�� ���� ����

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
