// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessLobbyHUD.h"
#include "Game/Widgets/ChessUserWidget.h"
#include "GCE.h"

AChessLobbyHUD::AChessLobbyHUD()
{

}

void AChessLobbyHUD::StartPlayHUD()
{
	HandlingWidgetImpl(LobbyWidget);
}

void AChessLobbyHUD::HandlingWidgetImpl(const TSubclassOf<UChessUserWidget>& Widget)
{
	if (CurrentWidget.IsValid())
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	auto NewWidget = GetInactivatedWidget(Widget);
	if (!NewWidget)
	{
		NewWidget = CreateWidget<UChessUserWidget>(GetWorld(), Widget);
		GCE_CHECK(nullptr != NewWidget);
	}

	NewWidget->AddToViewport();
	CurrentWidget = NewWidget;
}

UChessUserWidget* AChessLobbyHUD::GetInactivatedWidget(const TSubclassOf<UChessUserWidget>& Key) const
{
	if (auto Found = WidgetPool.Find(Key))
	{
		if (false == (*Found)->IsActivating())
		{
			return *Found;
		}
	}

	return nullptr;
}
