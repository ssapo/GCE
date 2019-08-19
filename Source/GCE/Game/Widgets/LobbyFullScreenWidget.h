// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Widgets/ChessUserWidget.h"
#include "LobbyFullScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class GCE_API ULobbyFullScreenWidget : public UChessUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
		void OnOnePlayerClikedImpl();

	UFUNCTION()
		void OnTwoPlayerClikedImpl();

	UFUNCTION()
		void OnNetworkPlayClikedImpl();

private:
	UPROPERTY(Meta = (BindWidget))
		class UButton* OnePlayerButton;

	UPROPERTY(Meta = (BindWidget))
		class UButton* TwoPlayersButton;

	UPROPERTY(Meta = (BindWidget))
		class UButton* NetworkPlayButton;

	class AChessLobbyMode* LobbyMode;
};
