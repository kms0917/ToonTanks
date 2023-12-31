// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();	//게임시작에 관한 함수(블루프린트에서 구현함)

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);	//게임 종료에 관한 함수(블루프린트에서 구현함)

private:

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TargetTower = 0;
	int32 GetTargetTowerCount();
};
