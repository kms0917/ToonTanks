// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float Speed = 700.f;
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float TurnRate = 90.f;


	void Move(float Value);
	void Turn(float Value);
	void Jump();
	APlayerController* TankPlayerController;
};
