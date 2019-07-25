// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"

TWeakObjectPtr<AChessPlayerController> AChessPlayerController::LocalPC;

AChessPlayerController::AChessPlayerController()
{
	GCE_LOG_S(Display);
}

void AChessPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	GCE_LOG_S(Display);

	LocalPC = this;
}

void AChessPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GCE_LOG_S(Display);
}

void AChessPlayerController::RestartLevel()
{
	Super::RestartLevel();
	GCE_LOG_S(Display);
}

void AChessPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GCE_LOG_S(Display);
}