// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/ChessUserWidget.h"
#include "ChessFullScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class GCE_API UChessFullScreenWidget : public UChessUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
		void OnSwitchButtonClickedImpl();

private:

	UPROPERTY(Meta = (BindWidget))
		class UButton* SwitchButton;
};
