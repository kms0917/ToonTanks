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

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 DashCount = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 JumpCount = 2;

	UFUNCTION(BlueprintCallable)
	void ManageDashCount();

	UFUNCTION(BlueprintCallable)
	void ManageJumpCount();

private:
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnyWhere, Category = "Components")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float Speed = 700.f;	//�̵��ӵ�
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float TurnRate = 90.f;	//ȸ�� �ӵ�

	UFUNCTION()
	void AddDashCount();

	UFUNCTION()
	void AddJumpCount();

	FTimerHandle DashCountTimerHandler;
	float DashCountRate = 4.5f;		//DashCount�� 4.5�ʿ� �ϳ��� ȸ��
	FTimerHandle JumpCountTimerHandler;
	float JumpCountRate = 3.f;		//JumpCount�� 3�ʿ� �ϳ��� ȸ��

	//�̵��� ������ �Լ���
	void Move(float Value);
	void Turn(float Value);
	void Jump();
	void Dash();
	APlayerController* TankPlayerController;
};
