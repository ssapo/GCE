// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Widgets/ChessUserWidget.h"
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
		void OnSwitchClickedImpl();

	UFUNCTION()
		void OnChange2DClickedImpl();

	UFUNCTION()
		void OnChange3DClickedImpl();

	UFUNCTION()
		void OnLockCameraMovingClickedImpl();

	UFUNCTION()
		void OnUnlockCameraMovingClickedImpl();

private:

	UPROPERTY(Meta = (BindWidget))
		class UButton* SwitchButton;

	UPROPERTY(Meta = (BindWidget))
		class UWidgetSwitcher* Toggle2DSwitcher;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Change2DButton;

	UPROPERTY(Meta = (BindWidget))
		class UButton* Change3DButton;

	UPROPERTY(Meta = (BindWidget))
		class UWidgetSwitcher* ToggleCameraMovingSwitcher;

	UPROPERTY(Meta = (BindWidget))
		class UButton* LockCameraMovingButton;

	UPROPERTY(Meta = (BindWidget))
		class UButton* UnlockCameraMovingButton;
};
