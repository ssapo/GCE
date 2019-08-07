// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChessUserWidget.generated.h"

UCLASS()
class GCE_API UChessUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
protected:
	class AChessGameMode* GetGameMode() const;

private:
	void SetGameMode();

private:
	class AChessGameMode* GameMode;
};
