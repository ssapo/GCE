// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessFullScreenWidget.h"
#include <Button.h>
#include <WidgetSwitcher.h>
#include "GCE.h"
#include "ChessGameModeBase.h"

void UChessFullScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SwitchButton)
	{
		SwitchButton->OnClicked.AddDynamic(this,
			&UChessFullScreenWidget::OnSwitchClickedImpl);
	}

	if (Change2DButton)
	{
		Change2DButton->OnClicked.AddDynamic(this, 
			&UChessFullScreenWidget::OnChange2DClickedImpl
		);
	}

	if (Change3DButton)
	{
		Change3DButton->OnClicked.AddDynamic(this, 
			&UChessFullScreenWidget::OnChange3DClickedImpl);
	}

	if (LockCameraMovingButton)
	{
		LockCameraMovingButton->OnClicked.AddDynamic(this, 
			&UChessFullScreenWidget::OnLockCameraMovingClickedImpl);
	}

	if (UnlockCameraMovingButton)
	{
		UnlockCameraMovingButton->OnClicked.AddDynamic(this, 
			&UChessFullScreenWidget::OnUnlockCameraMovingClickedImpl);
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

void UChessFullScreenWidget::OnSwitchClickedImpl()
{
	GetGameMode()->ChangeTeam();
}

void UChessFullScreenWidget::OnChange2DClickedImpl()
{
	GetGameMode()->Change2DCamera();
}

void UChessFullScreenWidget::OnChange3DClickedImpl()
{
	GetGameMode()->Change3DCamera();
}

void UChessFullScreenWidget::OnLockCameraMovingClickedImpl()
{
	GetGameMode()->LockCameraMoving();
}

void UChessFullScreenWidget::OnUnlockCameraMovingClickedImpl()
{
	GetGameMode()->UnlockCameraMoving();
}
