#include "Game/ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"
#include "ChessFuncs.h"
#include "Mover/ChessMoverComponent.h"
#include "Death/ChessDeathComponent.h"

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
		const EChessTeam& PrevChessActorTeam = ClickedCurrentActor->GetTeam();
		const EChessTeam& NewChessActorTeam = ChessActor->GetTeam();

		bool IsSameTeam = UChessFuncs::IsEqualTeam(NewChessActorTeam, PrevChessActorTeam);
		if (IsSameTeam)
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
		const EChessTeam& PrevChessActorTeam = ClickedCurrentActor->GetTeam();
		const EChessTeam& NewChessActorTeam = ChessActor->GetTeam();

		bool IsSameTeam = UChessFuncs::IsEqualTeam(NewChessActorTeam, PrevChessActorTeam);
		if (IsSameTeam)
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
	const EChessTeam& CurrentClickedActorTeam = CurrentIsNotNull->GetTeam();

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
	auto Component = ChessActor->GetComponentByClass(UChessMoverComponent::StaticClass());
	GCE_CHECK(nullptr != Component);

	auto Mover = Cast<UChessMoverComponent>(Component);
	GCE_CHECK(nullptr != Mover);

	FIntPoint NewPoint = Mover->GetCell();
	if (auto AttackedPiece = GetChessPieceFromMap(NewPoint))
	{
		auto Name = *AttackedPiece->GetName();

		// Process "eat chess piece"
		if (auto Death = AttackedPiece->FindComponentByClass<UChessDeathComponent>())
		{
			Death->WillDieItSelf();
			
			if (UChessFuncs::IsBlackKing(ChessActor->GetTeam(), Death->GetClass()))
			{
				GCE_LOG(Log, TEXT("White is Win check the [%s]"), Name);

				//GameOver();
			}
			else if (UChessFuncs::IsWhiteKing(ChessActor->GetTeam(), Death->GetClass()))
			{
				GCE_LOG(Log, TEXT("Black is Win check the [%s]"), Name);
				
				//GameOver();
			}
		}
		else
		{
			GCE_LOG(Log, TEXT("Find Component Death from [%s]"), Name);
		}
	}

	auto CurrActor = ChessPlayerPtr->GetCurrentClickedActor();
	GCE_CHECK(nullptr != CurrActor);

	auto CurrActorComponent = CurrActor->GetComponentByClass(UChessMoverComponent::StaticClass());
	GCE_CHECK(nullptr != Component);

	auto CurrActorMover = Cast<UChessMoverComponent>(CurrActorComponent);
	GCE_CHECK(nullptr != Mover);

	SetChessPieceIntoMap(CurrActor, NewPoint);

	CurrActorMover->SetCellPoint(NewPoint);
	CurrActorMover->SetFirstMove(false);

	ChessPlayerPtr->ChangeCurrentClickedActor(nullptr);

	bWaitAnimation = true;

	SetInvisibleAllCells();
}

void AChessGameMode::MovePieceCurrentIsOtherTeam(AChessActor* const ChessActor)
{
	ChessPlayerPtr->ChangeCurrentClickedActor(nullptr);

	SetInvisibleAllCells();
}