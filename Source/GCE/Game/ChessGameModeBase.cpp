// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"

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

	// ü�� �̵� Ÿ��
	{
		if (MovePieceClass)
		{
			for (int y = 0; y < 8; ++y)
			{
				for (int x = 0; x < 8; ++x)
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

	// ü�� ��
	{
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				FVector NewLocation = StartInitializeLocation;
				EChessActor Key = EChessActor(ChessStartMap[y * 8 + x]);
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
							continue;
						}
					}

					ChessGameMap.Add(nullptr);
				}
			}
		}
	}

	if (AChessPlayerController* PC = GetWorld()->GetFirstPlayerController<AChessPlayerController>())
	{
		ChessPlayerController = PC;
	}
}

void AChessGameMode::OnSelectedChessActor(AChessActor* const ChessActor)
{
	if (ChessActor->IsA(MovePieceClass))
	{
		if (ChessPlayerController.IsValid())
		{

			if (AChessActor* CurrActor = ChessPlayerController->GetCurrentClickedActor())
			{
				FIntPoint NewPoint = ChessActor->GetCell();

				if (AChessActor* AttackedPiece = ChessGameMap[NewPoint.Y * 8 + NewPoint.X])
				{
				}
					
				CurrActor->SetCellPoint(NewPoint);
			}
			ChessPlayerController->ChangeCurrentClickedActor(nullptr);

			for (const auto& e : ChessMoveMap)
			{
				if (e.IsValid())
				{
					e->SetVisiblity(false);
				}
			}
		}
	}
	else
	{
		if (ChessPlayerController.IsValid())
		{
			ChessPlayerController->ChangeCurrentClickedActor(ChessActor);

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
				FIntPoint CE = CurrPosition + e;
				TWeakObjectPtr<AChessActor> MovePieceActor = ChessMoveMap[CE.Y * 8 + CE.X];
				if (MovePieceActor.IsValid())
				{
					MovePieceActor->SetVisiblity(true);
				}
			}
		}
	}
}
