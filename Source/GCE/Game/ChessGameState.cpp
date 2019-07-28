// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameState.h"

bool AChessGameState::IsMatchInProgress() const
{
	//GCE_LOG_S(Log);
	return Super::IsMatchInProgress();
}

bool AChessGameState::HasMatchEnded() const
{
	//GCE_LOG_S(Log);
	return Super::HasMatchEnded();
}

void AChessGameState::HandleMatchIsWaitingToStart()
{
	//GCE_LOG_S(Log);
	Super::HandleMatchIsWaitingToStart();
}

void AChessGameState::HandleMatchHasStarted()
{
	//GCE_LOG_S(Log);
	Super::HandleMatchHasStarted();
}

void AChessGameState::HandleMatchHasEnded()
{
	//GCE_LOG_S(Log);
	Super::HandleMatchHasEnded();
}

void AChessGameState::HandleLeavingMap()
{
	//GCE_LOG_S(Log);
	Super::HandleLeavingMap();
}

void AChessGameState::OnRep_MatchState()
{
	//GCE_LOG_S(Log);
	Super::OnRep_MatchState();
}

void AChessGameState::OnRep_ElapsedTime()
{
	//GCE_LOG_S(Log);
	Super::OnRep_ElapsedTime();
}

void AChessGameState::DefaultTimer()
{
	//GCE_LOG_S(Log);
	Super::DefaultTimer();
}

bool AChessGameState::ShouldShowGore() const
{
	//GCE_LOG_S(Log);
	return Super::ShouldShowGore();
}

void AChessGameState::PostInitializeComponents()
{
	//GCE_LOG_S(Log);
	Super::PostInitializeComponents();
}

void AChessGameState::ReceivedGameModeClass()
{
	//GCE_LOG_S(Log);
	Super::ReceivedGameModeClass();
}

bool AChessGameState::HasMatchStarted() const
{
	//GCE_LOG_S(Log);
	return Super::HasMatchStarted();
}

void AChessGameState::HandleBeginPlay()
{
	//GCE_LOG_S(Log);
	Super::HandleBeginPlay();
}

float AChessGameState::GetPlayerStartTime(class AController* Controller) const
{
	//GCE_LOG_S(Log);
	return Super::GetPlayerStartTime(Controller);
}

float AChessGameState::GetPlayerRespawnDelay(class AController* Controller) const
{
	//GCE_LOG_S(Log);
	return Super::GetPlayerRespawnDelay(Controller);
}
