// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"
#include "ChessFuncs.h"
#include "ChessMoverComponent.h"
#include "ChessCameraPawn.h"
#include "Mover/PawnMoverComponent.h"

AChessGameMode::AChessGameMode()
{
	GCE_LOG_S(Log);

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
	WhiteCameraTransform.SetLocation(FVector(0.0f, -550.0f, 600.0f));
	WhiteCameraTransform.SetRotation(FQuat(FRotator(-50.0f, 90.0f, 0.0f)));
	BlackCameraTransform.SetLocation(FVector(0.0f, 550.0f, 600.0f));
	BlackCameraTransform.SetRotation(FQuat(FRotator(-50.0f, -90.0f, 0.0f)));
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

	GCE_CHECK(nullptr != ChessBoardClass);
	auto BoardClass = GetWorld()->SpawnActor<AChessActor>(ChessBoardClass);
	GCE_CHECK(nullptr != BoardClass);

	// 체스 이동 타일
	ChessMoveMap.Reset();
	if (nullptr == MovePieceClass)
	{
		GCE_LOG(Error, TEXT("nullptr == MovePieceClass"));
	}

	for (int32 Y = 0; Y < CHESS_HEIGHT; ++Y)
	{
		for (int32 X = 0; X < CHESS_WIDTH; ++X)
		{
			FVector NewLocation = StartInitializeLocation;
			if (AChessActor * Actor = GetWorld()->SpawnActor<AChessActor>(MovePieceClass))
			{
				Actor->SetVisiblity(false);
				Actor->OnSelected.AddUObject(this, &AChessGameMode::OnSelectedChessActor);
				Actor->SetActorLocation(NewLocation);

				//Actor->OnMovingEnd.AddUObject(this, &AChessGameMode::OnMovingEndChessActor);
				auto Component = Actor->GetComponentByClass(UChessMoverComponent::StaticClass());
				if (nullptr == Component) { continue; }

				auto Mover = Cast<UChessMoverComponent>(Component);
				if (nullptr == Mover) { continue; }

				Mover->SetIntervalVector(StartIntervalLocation);
				Mover->SetCellXY(X, Y);
				Mover->OnMovingEnd.AddUObject(this, &AChessGameMode::OnMovingEndChessActor);

				ChessMoveMap.Add(Actor);
			}
		}
	}

	// 체스 맵
	ChessGameMap.Reset();
	for (int32 Y = 0; Y < CHESS_HEIGHT; ++Y)
	{
		for (int32 X = 0; X < CHESS_WIDTH; ++X)
		{
			FVector NewLocation = StartInitializeLocation;
			EChessActor Key = EChessActor(ChessStartMap[Y * CHESS_WIDTH + X]);
			if (Key != EChessActor::NONE)
			{
				auto CBoard = ChessActors[Key];
				if (nullptr == CBoard) { continue; }

				auto Actor = GetWorld()->SpawnActor<AChessActor>(CBoard);
				if (nullptr == Actor) { continue; }

				Actor->SetActorLocation(NewLocation);
				Actor->SetVisiblity(true);
				Actor->OnSelected.AddUObject(this, &AChessGameMode::OnSelectedChessActor);

				auto Component = Actor->GetComponentByClass(UChessMoverComponent::StaticClass());
				if (nullptr == Component) { continue; }

				auto Mover = Cast<UChessMoverComponent>(Component);
				if (nullptr == Mover) { continue; }
				
				Mover->SetIntervalVector(StartIntervalLocation);
				Mover->SetCellXY(X, Y);
				Mover->OnMovingEnd.AddUObject(this, &AChessGameMode::OnMovingEndChessActor);
				
				ChessGameMap.Add(Actor);
			}
			else
			{
				ChessGameMap.Add(nullptr);
			}
		}
	}

	auto PC = GetWorld()->GetFirstPlayerController<AChessPlayerController>();
	GCE_CHECK(nullptr != PC);
	ChessPlayerPtr = PC;

	auto ChessCamera = Cast<AChessCameraPawn>(ChessPlayerPtr->GetPawn());
	GCE_CHECK(nullptr != ChessCamera);
	ChessCameraPtr = ChessCamera;

	SettingTeam(EChessTeam::White);

	bWaitAnimation = false;
}

void AChessGameMode::SettingTeam(const EChessTeam& Team)
{
	if (ChessCameraPtr.IsValid() && ChessPlayerPtr.IsValid())
	{
		ChessPlayerPtr->SetChoosenChessTeam(Team);
		ChessPlayerPtr->SetMyTurn(true);

		if (UChessFuncs::IsWhiteTeam(Team))
		{
			ChessCameraPtr->SetCameraTransform(WhiteCameraTransform);
		}
		else if (UChessFuncs::IsBlackTeam(Team))
		{
			ChessCameraPtr->SetCameraTransform(BlackCameraTransform);
		}
	}
}

void AChessGameMode::ChangeTeam()
{
	if (ChessCameraPtr.IsValid() && ChessPlayerPtr.IsValid())
	{
		auto Team = ChessPlayerPtr->GetChoosenChessTeam();
		if (UChessFuncs::IsWhiteTeam(Team))
		{
			SettingTeam(EChessTeam::Black);
		}
		else if (UChessFuncs::IsBlackTeam(Team))
		{
			SettingTeam(EChessTeam::White);
		}
	}
}

void AChessGameMode::Change2DCamera()
{
	if (ChessCameraPtr.IsValid())
	{
		ChessCameraPtr->SetCameraTransform(Chess2DCameraTransform);
	}
}

void AChessGameMode::Change3DCamera()
{
	if (ChessCameraPtr.IsValid())
	{
		ChessCameraPtr->SetCameraTransform(Chess2DCameraTransform);
	}
}

void AChessGameMode::LockCameraMoving()
{
	if (ChessCameraPtr.IsValid())
	{
		ChessCameraPtr->SetCameraMoving(true);
	}
}

void AChessGameMode::UnlockCameraMoving()
{
	if (ChessCameraPtr.IsValid())
	{
		ChessCameraPtr->SetCameraMoving(false);
	}
}

void AChessGameMode::OnSelectedChessActor(AChessActor* const ChessActor)
{
	if (bWaitAnimation)
	{
		GCE_LOG(Log, TEXT("bWaitAnimation is true so return logic"));

		return;
	}

	if (nullptr == ChessActor )
	{
		return;
	}

	if (ChessPlayerPtr.IsValid() && ChessPlayerPtr->IsMyTurn())
	{
		if (ChessActor->IsA(MovePieceClass))
		{
			ProcessClickedMovePiece(ChessActor);
		}
		else
		{
			ProcessClickedChessPiece(ChessActor);
		}
	}
}

void AChessGameMode::OnMovingEndChessActor(UChessMoverComponent* const Mover)
{
	bWaitAnimation = false;
}

void AChessGameMode::ProcessClickedChessPiece(AChessActor* const ChessActor)
{
	const EChessTeam& PlayerTeam = ChessPlayerPtr->GetChoosenChessTeam();
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

void AChessGameMode::SetChessPieceIntoMap(AChessActor* Actor, const FIntPoint& NewPoint)
{
	GCE_CHECK(Actor);

	auto Component = Actor->GetComponentByClass(UChessMoverComponent::StaticClass());
	GCE_CHECK(Component);

	auto Mover = Cast<UChessMoverComponent>(Component);
	GCE_CHECK(Mover);

	if (0 <= NewPoint.X && CHESS_WIDTH > NewPoint.X && 0 <= NewPoint.Y && CHESS_HEIGHT > NewPoint.Y)
	{
		FIntPoint PrevPoint = Mover->GetCell();
		if (PrevPoint == FIntPoint::NoneValue)
		{
			return;
		}

		ChessGameMap[NewPoint.Y * CHESS_WIDTH + NewPoint.X] = Actor;
		ChessGameMap[PrevPoint.Y * CHESS_WIDTH + PrevPoint.X] = nullptr;
	}
}

void AChessGameMode::SetInvisibleAllCells()
{
	for (const auto& e : ChessMoveMap)
	{
		if (e.IsValid())
		{
			e->SetVisiblity(false);
		}
	}
}

void AChessGameMode::SetVisibleMovableCells(AChessActor* const ChessActor)
{
	GCE_CHECK(nullptr != ChessActor);

	auto Component = ChessActor->GetComponentByClass(UChessMoverComponent::StaticClass());
	GCE_CHECK(nullptr != Component);

	auto ChessActorMover = Cast<UChessMoverComponent>(Component);
	GCE_CHECK(nullptr != ChessActorMover);

	FIntPoint CurrPosition = ChessActorMover->GetCell();
	TArray<FIntPoint> Directions = ChessActorMover->GetMoveDirections();
	EChessTeam TeamOfActor = ChessActor->GetChessTeam();
	bool bPersistance = ChessActorMover->IsPercistance();

	for (FIntPoint E : Directions)
	{
		if (ChessActorMover->HasTeamDirection() && UChessFuncs::IsBlackTeam(TeamOfActor))
		{
			E *= -1;
		}

		FIntPoint NextPosition = CurrPosition;
		bool bLocalPersistance = bPersistance;
		do
		{
			NextPosition += E;
			if (AChessActor * MoverPieceActor = GetMoverPieceFromMap(NextPosition))
			{
				MoverPieceActor->SetVisiblity(true);

				if (nullptr != GetChessPieceFromMap(NextPosition))
				{
					bLocalPersistance = false;
					MoverPieceActor->SetVisiblity(false);
				}
				else if (ChessActorMover->HasSpecialMove())
				{
					if (ChessActorMover->IsFirstMove())
					{
						// Pawn's first move (Y + 2)
						if (ChessActorMover->IsA(UPawnMoverComponent::StaticClass()))
						{
							NextPosition += E;

							if (AChessActor * MovePiece = GetMoverPieceFromMap(NextPosition))
							{
								if (nullptr != GetChessPieceFromMap(NextPosition))
								{
									MovePiece->SetVisiblity(false);
								}
								else
								{
									MovePiece->SetVisiblity(true);
								}
							}
						}
					}
					else
					{
						bLocalPersistance = false;
					}
				}
			}
			else
			{
				bLocalPersistance = false;
			}
		} while (bLocalPersistance);
	}

	CurrPosition = ChessActorMover->GetCell();
	Directions = ChessActorMover->GetAttackDirections();
	TeamOfActor = ChessActor->GetChessTeam();
	bPersistance = ChessActorMover->IsPercistance();

	for (FIntPoint E : Directions)
	{
		if (ChessActorMover->HasTeamDirection() && UChessFuncs::IsBlackTeam(TeamOfActor))
		{
			E *= -1;
		}

		FIntPoint NextPosition = CurrPosition;
		bool bLocalPersistance = bPersistance;
		do
		{
			NextPosition += E;
			if (auto MoverPieceActor = GetMoverPieceFromMap(NextPosition))
			{
				if (auto ChessPiece = GetChessPieceFromMap(NextPosition))
				{
					bLocalPersistance = false;
					if (!UChessFuncs::IsEqualTeam(TeamOfActor, ChessPiece->GetChessTeam()))
					{
						MoverPieceActor->SetVisiblity(true);
					}
				}
			}
			else
			{
				bLocalPersistance = false;
			}
		} while (bLocalPersistance);
	}
}

