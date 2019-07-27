// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "ChessPlayerController.h"
#include "ChessActor.h"

AChessGameModeBase::AChessGameModeBase()
{
	GCE_LOG_S(Log);

	PlayerControllerClass = AChessPlayerController::StaticClass();

	ChessMap = {
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

void AChessGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	GCE_LOG_S(Log);
	Super::InitGame(MapName, Options, ErrorMessage);
	GCE_LOG(Log, TEXT("%s%s%s"), *MapName, *Options, *ErrorMessage);
}

void AChessGameModeBase::StartPlay()
{
	Super::StartPlay();
	GCE_LOG_S(Log);

	auto BoardClass = ChessActors[EChessActor::Marble_Board];
	if (BoardClass)
	{
		GetWorld()->SpawnActor<AChessActor>(BoardClass);
	}

	if (ChessActors.Num() > 0)
	{
		float IX = StartIntervalLocation.X;
		float IY = StartIntervalLocation.Y;
		for (int y = 0; y < 8; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				FVector NewLocation = StartInitializeLocation + FVector(x * IX, y * IY, 0.0f);
				EChessActor Key = EChessActor(ChessMap[y * 8 + x]);
				if (Key != EChessActor::NONE)
				{
					auto BoardClass = ChessActors[Key];
					if (BoardClass)
					{
						GetWorld()->SpawnActor<AChessActor>(BoardClass, NewLocation, FRotator::ZeroRotator);
					}
				}
			}
		}
	}
}

void AChessGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	GCE_LOG_S(Log);
}

APlayerController* AChessGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	GCE_LOG_S(Log);
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AChessGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GCE_LOG_S(Log);
}

void AChessGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	GCE_LOG_S(Log);
}

void AChessGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GCE_LOG_S(Log);

}

