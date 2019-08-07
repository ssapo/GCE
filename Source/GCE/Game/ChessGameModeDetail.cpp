#include "Game/ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"
#include "ChessFuncs.h"
#include "ChessMoverComponent.h"

void AChessGameMode::ProcessPiecesAreSameTeam(AChessActor* const ChessActor)
{
	AChessActor* const ClickedCurrentActor = ChessPlayerPtr->GetCurrentClickedActor();
	if (nullptr == ClickedCurrentActor)
	{
		// Goto case 1.
		SameTeamCurrentIsNull(ChessActor);
	}
	else
	{
		const EChessTeam& PrevChessActorTeam = ClickedCurrentActor->GetChessTeam();
		const EChessTeam& NewChessActorTeam = ChessActor->GetChessTeam();

		if (UChessFuncs::IsEqualTeam(NewChessActorTeam, PrevChessActorTeam))
		{
			// Goto case 2.
			SameTeamCurrentIsSameTeam(ChessActor);
		}
		else
		{
			// Goto case 3.
			SameTeamCurrentIsOtherTeam(ChessActor);
		}
	}
}

void AChessGameMode::ProcessPiecesAreOtherTeam(AChessActor* const ChessActor)
{
	AChessActor* const ClickedCurrentActor = ChessPlayerPtr->GetCurrentClickedActor();
	if (nullptr == ClickedCurrentActor)
	{
		// Goto case 4.
		OtherTeamCurrentIsNull(ChessActor);
	}
	else
	{
		const EChessTeam& PrevChessActorTeam = ClickedCurrentActor->GetChessTeam();
		const EChessTeam& NewChessActorTeam = ChessActor->GetChessTeam();

		if (UChessFuncs::IsEqualTeam(NewChessActorTeam, PrevChessActorTeam))
		{
			// Goto case 5.
			OtherTeamCurrentIsSameTeam(ChessActor);
		}
		else
		{
			// Goto case 6.
			OtherTeamCurrentIsOtherTeam(ChessActor);
		}
	}
}

void AChessGameMode::ProcessClickedMovePiece(AChessActor* const ChessActor)
{
	AChessActor* const CurrentIsNotNull = ChessPlayerPtr->GetCurrentClickedActor();
	if (nullptr == CurrentIsNotNull)
	{
		GCE_LOG(Error, TEXT("AChessGameMode::ProcessClickedMovePiece(..) CurrentIsNotNull is Null"));
		return;
	}

	const EChessTeam& PlayerTeam = ChessPlayerPtr->GetChoosenChessTeam();
	const EChessTeam& CurrentClickedActorTeam = CurrentIsNotNull->GetChessTeam();

	if (UChessFuncs::IsEqualTeam(PlayerTeam, CurrentClickedActorTeam))
	{
		// Goto case 7.
		MovePieceCurrentIsSameTeam(ChessActor);
	}
	else
	{
		// Goto case 8.
		MovePieceCurrentIsOtherTeam(ChessActor);
	}
}

void AChessGameMode::SameTeamCurrentIsNull(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(ChessActor);

	SetVisibleMovableCells(ChessActor);
}

void AChessGameMode::SameTeamCurrentIsSameTeam(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();

	SetVisibleMovableCells(ChessActor);
}

void AChessGameMode::SameTeamCurrentIsOtherTeam(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();
	
	SetVisibleMovableCells(ChessActor);
}

void AChessGameMode::OtherTeamCurrentIsNull(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(ChessActor);

	SetVisibleMovableCells(ChessActor);
}

void AChessGameMode::OtherTeamCurrentIsSameTeam(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();

	SetVisibleMovableCells(ChessActor);
}

void AChessGameMode::OtherTeamCurrentIsOtherTeam(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();

	SetVisibleMovableCells(ChessActor);
}

void AChessGameMode::MovePieceCurrentIsSameTeam(AChessActor* const ChessActor)
{
	auto CurrActor = ChessPlayerPtr->GetCurrentClickedActor();
	GCE_CHECK(nullptr != CurrActor);

	auto Component = ChessActor->GetComponentByClass(UChessMoverComponent::StaticClass());
	GCE_CHECK(nullptr != Component);

	auto Mover = Cast<UChessMoverComponent>(Component);
	GCE_CHECK(nullptr != Mover);

	FIntPoint NewPoint = Mover->GetCell();
	if (AChessActor * const AttackedPiece = GetChessPieceFromMap(NewPoint))
	{
		if (AttackedPiece->Destroy())
		{
			GCE_LOG(Log, TEXT("Successs Destroy Actor [%s]"), *AttackedPiece->GetName());
		}
		else
		{
			GCE_LOG(Log, TEXT("Failed Destroy Actor [%s]"), *AttackedPiece->GetName());
		}
	}

	SetChessPieceIntoMap(CurrActor, NewPoint);

	Mover->SetCellPoint(NewPoint);

	ChessPlayerPtr->ChangeCurrentClickedActor(nullptr);

	SetInvisibleAllCells();

	bWaitAnimation = true;
}

void AChessGameMode::MovePieceCurrentIsOtherTeam(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(nullptr);

	SetInvisibleAllCells();
}