// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SubclassOf.h>
#include "GameFramework/HUD.h"
#include "ChessGameHUD.generated.h"

UCLASS()
class GCE_API AChessGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;


	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UChessUserWidget> InGameWidget;
};
