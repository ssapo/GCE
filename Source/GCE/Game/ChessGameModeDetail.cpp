#include "Game/ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"
#include "ChessFuncs.h"

void AChessGameMode::ProcessPiecesAreSameTeam(class AChessActor* const ChessActor)
{
	AChessActor* const ClickedCurrentActor = ChessPlayer->GetCurrentClickedActor();
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

void AChessGameMode::ProcessPiecesAreOtherTeam(class AChessActor* const ChessActor)
{
	AChessActor* const ClickedCurrentActor = ChessPlayer->GetCurrentClickedActor();
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

void AChessGameMode::ProcessClickedMovePiece(class AChessActor* const ChessActor)
{
	AChessActor* const CurrentIsNotNull = ChessPlayer->GetCurrentClickedActor();
	if (nullptr == CurrentIsNotNull)
	{
		GCE_LOG(Error, TEXT("AChessGameMode::ProcessClickedMovePiece(..) CurrentIsNotNull is Null"));
		return;
	}

	const EChessTeam& PlayerTeam = ChessPlayer->GetChoosenChessTeam();
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

void AChessGameMode::SameTeamCurrentIsNull(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	SetVisibleMovableCells(
		ChessActor->GetChessTeam(),
		ChessActor->GetCell(),
		ChessActor->GetDirections(),
		ChessActor->IsPersistance()
	);
}

void AChessGameMode::SameTeamCurrentIsSameTeam(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();

	SetVisibleMovableCells(
		ChessActor->GetChessTeam(),
		ChessActor->GetCell(),
		ChessActor->GetDirections(),
		ChessActor->IsPersistance()
	);
}

void AChessGameMode::SameTeamCurrentIsOtherTeam(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();
	
	SetVisibleMovableCells(
		ChessActor->GetChessTeam(),
		ChessActor->GetCell(),
		ChessActor->GetDirections(),
		ChessActor->IsPersistance()
	);
}

void AChessGameMode::OtherTeamCurrentIsNull(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	SetVisibleMovableCells(
		ChessActor->GetChessTeam(),
		ChessActor->GetCell(),
		ChessActor->GetDirections(),
		ChessActor->IsPersistance()
	);
}

void AChessGameMode::OtherTeamCurrentIsSameTeam(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();

	SetVisibleMovableCells(
		ChessActor->GetChessTeam(),
		ChessActor->GetCell(),
		ChessActor->GetDirections(),
		ChessActor->IsPersistance()
	);


}

void AChessGameMode::OtherTeamCurrentIsOtherTeam(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	SetInvisibleAllCells();

	SetVisibleMovableCells(
		ChessActor->GetChessTeam(),
		ChessActor->GetCell(),
		ChessActor->GetDirections(),
		ChessActor->IsPersistance()
	);
}

void AChessGameMode::MovePieceCurrentIsSameTeam(class AChessActor* const ChessActor)
{
	if (AChessActor * CurrActor = ChessPlayer->GetCurrentClickedActor())
	{
		FIntPoint NewPoint = ChessActor->GetCell();
		if (AChessActor * const AttackedPiece = GetChessPieceFromMap(NewPoint))
		{
			if (GetWorld()->DestroyActor(AttackedPiece))
			{
				GCE_LOG(Log, TEXT("Successs Destroy Actor [%s]"), *AttackedPiece->GetName());
			}
			else
			{
				GCE_LOG(Log, TEXT("Failed Destroy Actor [%s]"), *AttackedPiece->GetName());
			}
		}

		SetChessPieceIntoMap(CurrActor, NewPoint);
		CurrActor->SetCellPoint(NewPoint);
	}
	ChessPlayer->ChangeCurrentClickedActor(nullptr);

	SetInvisibleAllCells();
}

void AChessGameMode::MovePieceCurrentIsOtherTeam(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(nullptr);

	SetInvisibleAllCells();
}