// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/GameMode.h"
#include "ChessLobbyMode.generated.h"

UCLASS()
class GCE_API AChessLobbyMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AChessLobbyMode();

	virtual void StartPlay() override;

	void GoInGameOnePlayer();
	void GoInGameTwoPlayers();

private:

	TWeakObjectPtr<APlayerController> LobbyPlayerPtr;

	TWeakObjectPtr<class AChessLobbyHUD> LobbyHUDPtr;
};
