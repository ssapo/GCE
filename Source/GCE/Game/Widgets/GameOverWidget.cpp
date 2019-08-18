// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverWidget.h"
#include <Button.h>
#include "Game/ChessGameModeBase.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this,
			&UGameOverWidget::OnRestartClickedImpl);
	}

	if (LobbyButton)
	{
		RestartButton->OnClicked.AddDynamic(this,
			&UGameOverWidget::OnLobbyClickedImpl);
	}
}

void UGameOverWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UGameOverWidget::OnRestartClickedImpl()
{
	GetGameMode()->RestartGame();
}

void UGameOverWidget::OnLobbyClickedImpl()
{
	GetGameMode()->GoLobby();
}
