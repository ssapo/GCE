// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/GameState.h"
#include "ChessGameState.generated.h"

/**
 * 
 */
UCLASS()
class GCE_API AChessGameState : public AGameState
{
	GENERATED_BODY()
	
	virtual bool IsMatchInProgress() const override;
	virtual bool HasMatchEnded() const override;

protected:
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual void HandleLeavingMap() override;

public:
	virtual void OnRep_MatchState() override;
	virtual void OnRep_ElapsedTime() override;
	virtual void DefaultTimer() override;
	virtual bool ShouldShowGore() const override;
	virtual void PostInitializeComponents() override;
	virtual void ReceivedGameModeClass() override;
	virtual bool HasMatchStarted() const override;
	virtual void HandleBeginPlay() override;
	virtual float GetPlayerStartTime(class AController* Controller) const override;
	virtual float GetPlayerRespawnDelay(class AController* Controller) const override;
};
