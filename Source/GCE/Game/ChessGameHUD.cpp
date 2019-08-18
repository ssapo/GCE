// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameHUD.h"
#include "Widgets/ChessUserWidget.h"
#include "GCE.h"

AChessGameHUD::AChessGameHUD()
{
	CurrentWidget = nullptr;
}

void AChessGameHUD::StartPlayHUD()
{
	HandlingWidgetImpl(InGameWidget);
}

void AChessGameHUD::GameOverHUD()
{
	HandlingWidgetImpl(GameOverWidget);
}

void AChessGameHUD::HandlingWidgetImpl(const TSubclassOf<UChessUserWidget>& Widget)
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

UChessUserWidget* AChessGameHUD::GetInactivatedWidget(const TSubclassOf<UChessUserWidget>& Key) const
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
