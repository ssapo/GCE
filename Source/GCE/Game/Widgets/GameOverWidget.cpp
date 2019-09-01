// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverWidget.h"
#include <Button.h>
#include "Game/ChessGameModeBase.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto FoundGameMode = GetWorld()->GetAuthGameMode<AChessGameMode>();
	GCE_CHECK(nullptr != FoundGameMode);

	GameMode = FoundGameMode;

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this,
			&UGameOverWidget::OnRestartClickedImpl);
	}

	if (LobbyButton)
	{
		LobbyButton->OnClicked.AddDynamic(this,
			&UGameOverWidget::OnLobbyClickedImpl);
	}
}

void UGameOverWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UGameOverWidget::OnRestartClickedImpl()
{
	GameMode->RestartGame();
}

void UGameOverWidget::OnLobbyClickedImpl()
{
	GameMode->GoLobby();
}