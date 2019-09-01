// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessFullScreenWidget.h"
#include <Button.h>
#include <WidgetSwitcher.h>
#include "GCE.h"
#include "Game/ChessGameModeBase.h"
#include "WidgetAnimation.h"
#include "UMGSequencePlayer.h"

void UChessFullScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto FoundGameMode = GetWorld()->GetAuthGameMode<AChessGameMode>();
	GCE_CHECK(nullptr != FoundGameMode);

	GameMode = FoundGameMode;

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

	if (StartAnim)
	{
		PlayAnimation(StartAnim);
	}
}

void UChessFullScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (SwitchButton)
	{
		SwitchButton->OnClicked.RemoveAll(this);
	}

	if (Change2DButton)
	{
		Change2DButton->OnClicked.RemoveAll(this);
	}

	if (Change3DButton)
	{
		Change3DButton->OnClicked.RemoveAll(this);
	}

	if (LockCameraMovingButton)
	{
		LockCameraMovingButton->OnClicked.RemoveAll(this);
	}

	if (UnlockCameraMovingButton)
	{
		UnlockCameraMovingButton->OnClicked.RemoveAll(this);
	}
}

void UChessFullScreenWidget::OnSwitchClickedImpl()
{
	GameMode->ChangeTeam(false);
}

void UChessFullScreenWidget::OnChange2DClickedImpl()
{
	GameMode->Change2DCamera();
}

void UChessFullScreenWidget::OnChange3DClickedImpl()
{
	GameMode->Change3DCamera();
}

void UChessFullScreenWidget::OnLockCameraMovingClickedImpl()
{
	GameMode->LockCameraMoving();
}

void UChessFullScreenWidget::OnUnlockCameraMovingClickedImpl()
{
	GameMode->UnlockCameraMoving();
}
