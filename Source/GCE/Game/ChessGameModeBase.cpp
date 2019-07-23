// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameModeBase.h"
#include "ChessPlayerController.h"

AChessGameModeBase::AChessGameModeBase()
{
	GCE_LOG_S(Display);

	PlayerControllerClass = AChessPlayerController::StaticClass();
}

void AChessGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	GCE_LOG_S(Display);
	Super::InitGame(MapName, Options, ErrorMessage);
	GCE_LOG(Display, TEXT("%s%s%s"), *MapName, *Options, *ErrorMessage);
}

void AChessGameModeBase::StartPlay()
{
	Super::StartPlay();
	GCE_LOG_S(Display);
}

void AChessGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	GCE_LOG_S(Display);
}

APlayerController* AChessGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	GCE_LOG_S(Display);
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void AChessGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	GCE_LOG_S(Display);
}

void AChessGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	GCE_LOG_S(Display);
}

