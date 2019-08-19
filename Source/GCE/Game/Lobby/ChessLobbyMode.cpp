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
