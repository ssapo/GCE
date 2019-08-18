// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Widgets/ChessUserWidget.h"
#include "GameOverWidget.generated.h"

UCLASS()
class GCE_API UGameOverWidget : public UChessUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
		void OnRestartClickedImpl();

	UFUNCTION()
		void OnLobbyClickedImpl();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* LobbyButton;
};
