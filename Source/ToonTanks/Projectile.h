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
	class UProjectileMovementComponent* ProjectileMovementComponent;	//발사체의 이동을 위한 변수 

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpurse, const FHitResult& Hit);	//발사체를 맞췄을때 실행시킬 함수

	UPROPERTY(EditAnyWhere)
	float Damage = 10.f;	//발사체의 데미지

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;	//발사체가 터질때의 이펙트

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;	//발사체의 궤적의 이펙트

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;	//발사체 발사 소리

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;		//발사체가 터질때의 소리

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;	//발사체가 터질때 카메라 쉐이크를 실행시키기 위한 변수

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
