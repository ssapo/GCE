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

	ChessGameMap = {
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

	TArray<int32> CopiedMap = ChessGameMap;

	// 체스 이동 타일
	{
		float IX = StartIntervalLocation.X;
		float IY = StartIntervalLocation.Y;
		if (SelectableActorClass)
		{
			for (int y = 0; y < 8; ++y)
			{
				for (int x = 0; x < 8; ++x)
				{
					FVector NewLocation = StartInitializeLocation + FVector(x * IX, y * IY, 0.0f);
					if (AChessActor * Actor = GetWorld()->SpawnActor<AChessActor>(SelectableActorClass,
						NewLocation, FRotator::ZeroRotator))
					{
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
	{
		float IX = StartIntervalLocation.X;
		float IY = StartIntervalLocation.Y;
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				FVector NewLocation = StartInitializeLocation + FVector(x * IX, y * IY, 0.0f);
				EChessActor Key = EChessActor(CopiedMap[y * 8 + x]);
				if (Key != EChessActor::NONE)
				{
					if (UClass* BoardClass = ChessActors[Key])
					{
						if (AChessActor* Actor = GetWorld()->SpawnActor<AChessActor>(BoardClass,
							NewLocation, FRotator::ZeroRotator))
						{
							Actor->SetCellXY(x, y);
							Actor->SetVisiblity(true);
							Actor->OnSelected.AddUObject(this, &AChessGameMode::OnSelectedChessActor);
						}
					}
				}
			}
		}
	}

	if (AChessPlayerController* PC = GetWorld()->GetFirstPlayerController<AChessPlayerController>())
	{
		ChessPlayerController = PC;
	}
}

void AChessGameMode::OnSelectedChessActor(class AChessActor* const ChessActor)
{
	if (ChessActor->IsA(SelectableActorClass))
	{
		if (ChessPlayerController.IsValid())
		{
			ChessPlayerController->ChangeCurrentClickedActor(ChessActor);

			for (const auto& Each : ChessMoveMap)
			{
				if (Each.IsValid())
				{
					Each->SetVisiblity(false);
				}
			}
		}
	}
	else
	{
		if (ChessPlayerController.IsValid())
		{
			ChessPlayerController->ChangeCurrentClickedActor(ChessActor);

			//ChessActor->GetCell();
			for (const auto& Each : ChessMoveMap)
			{
				if (Each.IsValid())
				{
					Each->SetVisiblity(true);
				}
			}
		}
	}
}
