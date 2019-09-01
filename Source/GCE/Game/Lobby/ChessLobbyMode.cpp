// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessLobbyMode.h"
#include "ChessLobbyHUD.h"

AChessLobbyMode::AChessLobbyMode()
{

}

void AChessLobbyMode::StartPlay()
{
	Super::StartPlay();

	auto PC = GetWorld()->GetFirstPlayerController();
	GCE_CHECK(nullptr != PC);
	LobbyPlayerPtr = PC;

	auto HUD = LobbyPlayerPtr->GetHUD();
	GCE_CHECK(nullptr != HUD);
	
	auto LobbyHUD = Cast<AChessLobbyHUD>(HUD);
	GCE_CHECK(nullptr != LobbyHUD);
	LobbyHUDPtr = LobbyHUD;
	LobbyHUDPtr->StartPlayHUD();
}

void AChessLobbyMode::GoInGameOnePlayer()
{
	UGameplayStatics::OpenLevel(this, TEXT("ChessOnePlayer"), true, TEXT("Players=1"));
}

void AChessLobbyMode::GoInGameTwoPlayers()
{
	UGameplayStatics::OpenLevel(this, TEXT("ChessTwoPlayers"), true, TEXT("Players=2"));
}
