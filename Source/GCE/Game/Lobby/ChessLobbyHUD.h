// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ChessLobbyHUD.generated.h"

class UChessUserWidget;

UCLASS()
class GCE_API AChessLobbyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AChessLobbyHUD();

	void StartPlayHUD();

private:
	void HandlingWidgetImpl(const TSubclassOf<UChessUserWidget>& Widget);

	UChessUserWidget* GetInactivatedWidget(const TSubclassOf<UChessUserWidget>& Key) const;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
		TSubclassOf<UChessUserWidget> LobbyWidget;

	TMap<TSubclassOf<UChessUserWidget>, UChessUserWidget*> WidgetPool;

	TWeakObjectPtr<UChessUserWidget> CurrentWidget;
};
