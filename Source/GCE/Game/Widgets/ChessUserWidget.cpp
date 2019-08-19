// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessUserWidget.h"
#include "Game/ChessGameModeBase.h"

void UChessUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bActivated = true;
}

void UChessUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	bActivated = false;
}

bool UChessUserWidget::IsActivating() const
{
	return bActivated;
}