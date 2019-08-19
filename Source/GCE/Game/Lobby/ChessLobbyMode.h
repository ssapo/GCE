// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ChessLobbyMode.generated.h"

class UChessUserWidget;

UCLASS()
class GCE_API AChessLobbyMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AChessLobbyMode();

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
