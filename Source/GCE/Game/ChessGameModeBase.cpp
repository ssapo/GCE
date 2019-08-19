// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"
#include "ChessGameState.h"
#include "ChessPlayerState.h"
#include "ChessFuncs.h"
#include "Mover/ChessMoverComponent.h"
#include "ChessCameraPawn.h"
#include "Mover/PawnMoverComponent.h"
#include "InGame/ChessGameHUD.h"

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
	MoverWaitAnimPool.Reset();
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
				Mover->SetCell(X, Y, true);
				MoverWaitAnimPool.Add(Mover, true);
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
				Mover->SetCell(X, Y, true);
				Mover->OnMovingEnd.AddUObject(this, &AChessGameMode::OnMovingEndChessActor);
				
				MoverWaitAnimPool.Add(Mover);
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

	auto HUD = ChessPlayerPtr->GetHUD();
	GCE_CHECK(nullptr != HUD);

	auto ChessHUD = Cast<AChessGameHUD>(HUD);
	GCE_CHECK(nullptr != ChessHUD);
	ChessGameHUD = ChessHUD;
	ChessGameHUD->StartPlayHUD();

	auto ChessCamera = Cast<AChessCameraPawn>(ChessPlayerPtr->GetPawn());
	GCE_CHECK(nullptr != ChessCamera);
	ChessCameraPtr = ChessCamera;

	SettingTeam(EChessTeam::White, true);

	bWaitAnimation = true;
	bGameOver = false;
}

void AChessGameMode::GameOver()
{
	if (ChessGameHUD.IsValid())
	{
		ChessGameHUD->GameOverHUD();
	}

	bGameOver = true;
}

void AChessGameMode::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ChessMap.Map"), false);
}

void AChessGameMode::GoLobby()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby.Map"), false);
}

void AChessGameMode::SettingTeam(const EChessTeam& Team, bool bFirst)
{
	if (ChessCameraPtr.IsValid() && ChessPlayerPtr.IsValid())
	{
		ChessPlayerPtr->SetChoosenChessTeam(Team);

		if (UChessFuncs::IsWhiteTeam(Team))
		{
			if (bFirst)
			{
				ChessPlayerPtr->SetMyTurn(true);
			}

			ChessCameraPtr->SetCameraTransform(WhiteCameraTransform);
		}
		else if (UChessFuncs::IsBlackTeam(Team))
		{
			if (bFirst)
			{
				ChessPlayerPtr->SetMyTurn(true);
			}

			ChessCameraPtr->SetCameraTransform(BlackCameraTransform);
		}
	}
}

void AChessGameMode::ChangeTeam(bool bFirst)
{
	if (ChessCameraPtr.IsValid() && ChessPlayerPtr.IsValid())
	{
		auto Team = ChessPlayerPtr->GetChoosenChessTeam();
		if (UChessFuncs::IsWhiteTeam(Team))
		{
			SettingTeam(EChessTeam::Black, bFirst);
		}
		else if (UChessFuncs::IsBlackTeam(Team))
		{
			SettingTeam(EChessTeam::White, bFirst);
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
	if (bGameOver && bWaitAnimation)
	{
		GCE_LOG(Log, TEXT("Entered logic return to ingore"));

		return;
	}

	if (nullptr == ChessActor)
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
	if (auto FoundNotNull = MoverWaitAnimPool.Find(Mover))
	{
		*FoundNotNull = false;
	}

	TArray<bool> Values;
	MoverWaitAnimPool.GenerateValueArray(Values);
	GCE_CHECK(Values.Num() > 0);

	for (bool E : Values)
	{
		if (E)
		{
			return;
		}
	}

	bWaitAnimation = false;
	ChangeTeam(true);
}

void AChessGameMode::ProcessClickedChessPiece(AChessActor* const ChessActor)
{
	const EChessTeam& PlayerTeam = ChessPlayerPtr->GetChoosenChessTeam();
	const EChessTeam& SelectedActorTeam = ChessActor->GetTeam();

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

	auto Mover = Actor->FindComponentByClass<UChessMoverComponent>();
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

	auto ChessActorMover = ChessActor->FindComponentByClass<UChessMoverComponent>();
	GCE_CHECK(nullptr != ChessActorMover);

	FIntPoint CurrPosition = ChessActorMover->GetCell();
	TArray<FIntPoint> Directions = ChessActorMover->GetMoveDirections();
	EChessTeam TeamOfActor = ChessActor->GetTeam();
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
	TeamOfActor = ChessActor->GetTeam();
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
					if (!UChessFuncs::IsEqualTeam(TeamOfActor, ChessPiece->GetTeam()))
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

