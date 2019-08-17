// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessUserWidget.h"
#include "Game/ChessGameModeBase.h"

void UChessUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetGameMode();
}

void UChessUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UChessUserWidget::SetGameMode()
{
	auto FoundGameMode = GetWorld()->GetAuthGameMode<AChessGameMode>();
	GCE_CHECK(nullptr != FoundGameMode);

	GameMode = FoundGameMode;
}

AChessGameMode* UChessUserWidget::GetGameMode() const
{
	return GameMode;
}
