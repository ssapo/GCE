// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"
#include "ChessActor.h"

TWeakObjectPtr<AChessPlayerController> AChessPlayerController::LocalPC;

AChessPlayerController* const AChessPlayerController::GetLocalPC()
{
	if (LocalPC.IsValid())
	{
		return LocalPC.Get();
	}

	return nullptr;
}

AChessPlayerController::AChessPlayerController()
{
	GCE_LOG_S(Log);

	bShowMouseCursor = true;
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
}

void AChessPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	GCE_LOG_S(Log);

	LocalPC = this;
}

void AChessPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GCE_LOG_S(Log);
}

void AChessPlayerController::RestartLevel()
{
	Super::RestartLevel();
	GCE_LOG_S(Log);
}

void AChessPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GCE_LOG_S(Log);
}

void AChessPlayerController::ChangeCurrentClickedActor(AChessActor* ClickedActor)
{
	if (CurrentClickedActor.IsValid())
	{
		CurrentClickedActor->SetOutlineEffect(false);
	}

	CurrentClickedActor = ClickedActor;
	CurrentClickedActor->SetOutlineEffect(true);

	GCE_LOG_S(Log);
}
