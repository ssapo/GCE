// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessFuncs.h"

AChessPlayerController::AChessPlayerController()
{
	GCE_LOG_S(Log);

	bShowMouseCursor = true;
	bEnableTouchEvents = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
}

void AChessPlayerController::ChangeCurrentClickedActor(AChessActor* ClickedActor)
{
	if (CurrentClickedActor.IsValid())
	{
		CurrentClickedActor->SetOutlineEffect(false);
	}

	CurrentClickedActor = ClickedActor;
	if (nullptr != CurrentClickedActor)
	{
		CurrentClickedActor->SetOutlineEffect(true);
	}
}

FORCEINLINE AChessActor* AChessPlayerController::GetCurrentClickedActor() const
{
	if (CurrentClickedActor.IsValid())
	{
		return CurrentClickedActor.Get();
	}

	return nullptr;
}

FORCEINLINE void AChessPlayerController::SetChoosenChessTeam(const EChessTeam& Team)
{
	ChoosenChessTeam = Team;
}

FORCEINLINE EChessTeam AChessPlayerController::GetChoosenChessTeam() const
{
	return ChoosenChessTeam;
}

FORCEINLINE EChessTeam AChessPlayerController::GetOpponentTeam() const
{
	return UChessFuncs::GetOpponentTeam(ChoosenChessTeam);
}

FORCEINLINE void AChessPlayerController::SetMyTurn(bool Value)
{
	bMyTurn = Value;
}

FORCEINLINE bool AChessPlayerController::IsMyTurn() const
{
	return bMyTurn;
}
