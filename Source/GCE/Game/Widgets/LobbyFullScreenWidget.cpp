// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyFullScreenWidget.h"
#include "Button.h"
#include "GCE.h"
#include "Game/Lobby/ChessLobbyMode.h"

void ULobbyFullScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto FoundLobbyMode = GetWorld()->GetAuthGameMode<AChessLobbyMode>();
	GCE_CHECK(nullptr != FoundLobbyMode);

	LobbyMode = FoundLobbyMode;

	if (OnePlayerButton)
	{
		OnePlayerButton->OnClicked.AddDynamic(this,
			&ULobbyFullScreenWidget::OnOnePlayerClikedImpl);
	}

	if (TwoPlayersButton)
	{
		TwoPlayersButton->OnClicked.AddDynamic(this,
			&ULobbyFullScreenWidget::OnTwoPlayerClikedImpl);
	}

	if (NetworkPlayButton)
	{
		NetworkPlayButton->OnClicked.AddDynamic(this,
			&ULobbyFullScreenWidget::OnNetworkPlayClikedImpl);
	}
}

void ULobbyFullScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (OnePlayerButton)
	{
		OnePlayerButton->OnClicked.RemoveAll(this);
	}

	if (TwoPlayersButton)
	{
		TwoPlayersButton->OnClicked.RemoveAll(this);
	}

	if (NetworkPlayButton)
	{
		NetworkPlayButton->OnClicked.RemoveAll(this);
	}
}

void ULobbyFullScreenWidget::OnOnePlayerClikedImpl()
{
	GCE_LOG_S(Log);
}

void ULobbyFullScreenWidget::OnTwoPlayerClikedImpl()
{
	GCE_LOG_S(Log);
}

void ULobbyFullScreenWidget::OnNetworkPlayClikedImpl()
{
	GCE_LOG_S(Log);
}
