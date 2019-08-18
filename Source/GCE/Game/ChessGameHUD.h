// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SubclassOf.h>
#include "GameFramework/HUD.h"
#include "ChessGameHUD.generated.h"

class UChessUserWidget;

UCLASS()
class GCE_API AChessGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AChessGameHUD();

	void StartPlayHUD();
	void GameOverHUD();

private:
	void HandlingWidgetImpl(const TSubclassOf<UChessUserWidget>& Widget);
	UChessUserWidget* GetInactivatedWidget(const TSubclassOf<UChessUserWidget>& Key) const;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
		TSubclassOf<UChessUserWidget> InGameWidget;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
		TSubclassOf<UChessUserWidget> GameOverWidget;

	TMap<TSubclassOf<UChessUserWidget>, UChessUserWidget*> WidgetPool;

	TWeakObjectPtr<UChessUserWidget> CurrentWidget;
};
