// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessFullScreenWidget.h"
#include <Button.h>
#include "GCE.h"
#include "ChessGameModeBase.h"

void UChessFullScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SwitchButton)
	{
		SwitchButton->OnClicked.AddDynamic(this, &UChessFullScreenWidget::OnSwitchButtonClickedImpl);
	}
}

void UChessFullScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (SwitchButton)
	{
		SwitchButton->OnClicked.RemoveAll(this);
	}
}

void UChessFullScreenWidget::OnSwitchButtonClickedImpl()
{
	GetGameMode()->ChangeTeam();
}
