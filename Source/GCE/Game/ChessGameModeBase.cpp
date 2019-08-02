// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"
#include "ChessFuncs.h"

AChessGameMode::AChessGameMode()
{
	GCE_LOG_S(Log);

	PlayerControllerClass = AChessPlayerController::StaticClass();
	PlayerStateClass = AChessPlayerState::StaticClass();
	GameStateClass = AChessGameState::StaticClass();

	ChessStartMap = {
		4,	3,	5,	6,	7,	5, 3, 4,
		2,	2,	2,	2,	2,	2, 2, 2,
		0,  0,  0,  0,  0,  0, 0, 0,
		0,  0,  0,  0,  0,  0, 0, 0,
		0,  0,  0,  0,  0,  0, 0, 0,
		0,  0,  0,  0,  0,  0, 0, 0,
		8,	8,	8,	8,	8,	8, 8, 8,
		10, 9, 11, 12, 13, 11, 9, 10,
	};

	StartInitializeLocation = FVector(-350.0f, -350.0f, 50.0f);
	StartIntervalLocation = FVector(100.0f, 100.0f, 0.0f);
}

void AChessGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	GCE_LOG_S(Log);
	Super::InitGame(MapName, Options, ErrorMessage);
	GCE_LOG(Log, TEXT("%s%s%s"), *MapName, *Options, *ErrorMessage);
}

void AChessGameMode::StartPlay()
{
	Super::StartPlay();

	if (ChessBoardClass)
	{
		if (AChessActor* Board = GetWorld()->SpawnActor<AChessActor>(ChessBoardClass))
		{
		}
	}

	// 체스 이동 타일
	ChessMoveMap.Reset();
	{
		if (MovePieceClass)
		{
			for (int y = 0; y < CHESS_HEIGHT; ++y)
			{
				for (int x = 0; x < CHESS_WIDTH; ++x)
				{
					FVector NewLocation = StartInitializeLocation;
					if (AChessActor * Actor = GetWorld()->SpawnActor<AChessActor>(MovePieceClass,
						NewLocation, FRotator::ZeroRotator))
					{
						Actor->SetIntervalVector(StartIntervalLocation);
						Actor->SetCellXY(x, y);
						Actor->SetVisiblity(false);
						Actor->OnSelected.AddUObject(this, &AChessGameMode::OnSelectedChessActor);

						ChessMoveMap.Add(Actor);
					}
				}
			}
		}
	}

	// 체스 맵
	ChessGameMap.Reset();
	{
		for (int y = 0; y < CHESS_HEIGHT; ++y)
		{
			for (int x = 0; x < CHESS_WIDTH; ++x)
			{
				FVector NewLocation = StartInitializeLocation;
				EChessActor Key = EChessActor(ChessStartMap[y * CHESS_WIDTH + x]);
				if (Key != EChessActor::NONE)
				{
					if (UClass* BoardClass = ChessActors[Key])
					{
						if (AChessActor* Actor = GetWorld()->SpawnActor<AChessActor>(BoardClass,
							NewLocation, FRotator::ZeroRotator))
						{
							Actor->SetIntervalVector(StartIntervalLocation);
							Actor->SetCellXY(x, y);
							Actor->SetVisiblity(true);
							Actor->OnSelected.AddUObject(this, &AChessGameMode::OnSelectedChessActor);

							ChessGameMap.Add(Actor);
						}
					}
				}
				else
				{
					ChessGameMap.Add(nullptr);
				}
			}
		}
	}

	if (AChessPlayerController* PC = GetWorld()->GetFirstPlayerController<AChessPlayerController>())
	{
		ChessPlayer = PC;
	}
}

void AChessGameMode::OnSelectedChessActor(AChessActor* const ChessActor)
{
	if (nullptr == ChessActor)
	{
		return;
	}

	bool IsValid = ChessPlayer.IsValid();
	if (!IsValid)
	{
		return;
	}

	if (ChessActor->IsA(MovePieceClass))
	{
		ProcessClickedMovePiece(ChessActor);
	}
	else
	{
		ProcessClickedChessPiece(ChessActor);
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

void AChessGameMode::ProcessClickedChessPiece(class AChessActor* const ChessActor)
{
	const EChessTeam& PlayerTeam = ChessPlayer->GetChoosenChessTeam();
	const EChessTeam& SelectedActorTeam = ChessActor->GetChessTeam();

	if (UChessFuncs::IsEqualTeam(PlayerTeam, SelectedActorTeam))
	{
		ProcessPiecesAreSameTeam(ChessActor);
	}
	else
	{
		ProcessPiecesAreOtherTeam(ChessActor);
	}
}

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


void AChessGameMode::SameTeamCurrentIsNull(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	FIntPoint CurrPosition = ChessActor->GetCell();
	TArray<FIntPoint> Directions = ChessActor->GetDirections();

	for (const auto& e : ChessMoveMap)
	{
		if (e.IsValid())
		{
			e->SetVisiblity(false);
		}
	}

	for (const FIntPoint& e : Directions)
	{
		FIntPoint NextPosition = CurrPosition;
		bool bPersistance = ChessActor->IsPersistance();
		do
		{
			NextPosition += e;
			if (AChessActor * MoverPieceActor = GetMoverPieceFromMap(NextPosition))
			{
				MoverPieceActor->SetVisiblity(true);

				if (AChessActor * ChessPiece = GetChessPieceFromMap(NextPosition))
				{
					bPersistance = false;

					if (UChessFuncs::IsEqualTeamBetweenTwoActors(ChessActor, ChessPiece))
					{
						MoverPieceActor->SetVisiblity(false);
					}
				}
			}
			else
			{
				bPersistance = false;
			}
		} while (bPersistance);
	}
}

void AChessGameMode::SameTeamCurrentIsSameTeam(class AChessActor* const ChessActor)
{
	ChessPlayer->ChangeCurrentClickedActor(ChessActor);

	FIntPoint CurrPosition = ChessActor->GetCell();
	TArray<FIntPoint> Directions = ChessActor->GetDirections();

	for (const auto& e : ChessMoveMap)
	{
		if (e.IsValid())
		{
			e->SetVisiblity(false);
		}
	}

	for (const FIntPoint& e : Directions)
	{
		FIntPoint NextPosition = CurrPosition;
		bool bPersistance = ChessActor->IsPersistance();
		do
		{
			NextPosition += e;
			if (AChessActor * MoverPieceActor = GetMoverPieceFromMap(NextPosition))
			{
				MoverPieceActor->SetVisiblity(true);

				if (AChessActor * ChessPiece = GetChessPieceFromMap(NextPosition))
				{
					bPersistance = false;

					if (UChessFuncs::IsEqualTeamBetweenTwoActors(ChessActor, ChessPiece))
					{
						MoverPieceActor->SetVisiblity(false);
					}
				}
			}
			else
			{
				bPersistance = false;
			}
		} while (bPersistance);
	}
}

void AChessGameMode::SameTeamCurrentIsOtherTeam(class AChessActor* const ChessActor)
{

}

void AChessGameMode::OtherTeamCurrentIsNull(class AChessActor* const ChessActor)
{

}

void AChessGameMode::OtherTeamCurrentIsSameTeam(class AChessActor* const ChessActor)
{

}

void AChessGameMode::OtherTeamCurrentIsOtherTeam(class AChessActor* const ChessActor)
{

}

void AChessGameMode::MovePieceCurrentIsSameTeam(class AChessActor* const ChessActor)
{
	if (AChessActor * CurrActor = ChessPlayer->GetCurrentClickedActor())
	{
		FIntPoint NewPoint = ChessActor->GetCell();
		if (AChessActor * const AttackedPiece = GetChessPieceFromMap(NewPoint))
		{
		}

		SetChessPieceIntoMap(CurrActor, NewPoint);
		CurrActor->SetCellPoint(NewPoint);
	}
	ChessPlayer->ChangeCurrentClickedActor(nullptr);

	for (const auto& e : ChessMoveMap)
	{
		if (e.IsValid())
		{
			e->SetVisiblity(false);
		}
	}
}

void AChessGameMode::MovePieceCurrentIsOtherTeam(class AChessActor* const ChessActor)
{

}

AChessActor* AChessGameMode::GetMoverPieceFromMap(const FIntPoint& Point) const
{
	if (0 <= Point.X && CHESS_WIDTH > Point.X && 0 <= Point.Y && CHESS_HEIGHT > Point.Y)
	{
		auto WeakPtr = ChessMoveMap[Point.Y * CHESS_WIDTH + Point.X];
		if (WeakPtr.IsValid())
		{
			GCE_LOG(Log, TEXT("GetMoverPieceFromMap X: %d Y: %d"), Point.X, Point.Y);
			return WeakPtr.Get();
		}
	}

	return nullptr;
}

AChessActor* AChessGameMode::GetChessPieceFromMap(const FIntPoint& Point) const
{
	if (0 <= Point.X && CHESS_WIDTH > Point.X && 0 <= Point.Y && CHESS_HEIGHT > Point.Y)
	{
		auto WeakPtr = ChessGameMap[Point.Y * CHESS_WIDTH + Point.X];
		if (WeakPtr.IsValid())
		{
			GCE_LOG(Log, TEXT("GetChessPieceFromMap X: %d Y: %d"), Point.X, Point.Y);
			return WeakPtr.Get();
		}
	}
	return nullptr;
}

void AChessGameMode::SetChessPieceIntoMap(class AChessActor* Actor, const FIntPoint& NewPoint)
{
	if (0 <= NewPoint.X && CHESS_WIDTH > NewPoint.X && 0 <= NewPoint.Y && CHESS_HEIGHT > NewPoint.Y)
	{
		FIntPoint PrevPoint = Actor->GetCell();
		if (PrevPoint == FIntPoint::NoneValue)
		{
			return;
		}

		ChessGameMap[NewPoint.Y * CHESS_WIDTH + NewPoint.X] = Actor;
		ChessGameMap[PrevPoint.Y * CHESS_WIDTH + PrevPoint.X] = nullptr;
	}
}