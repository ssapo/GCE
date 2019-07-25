// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/PlayerController.h"
#include <WeakObjectPtrTemplates.h>
#include "ChessPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GCE_API AChessPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AChessPlayerController();

	virtual void ReceivedPlayer() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void RestartLevel() override;
	virtual void BeginPlay() override;

private:
	static TWeakObjectPtr<AChessPlayerController> LocalPC;

};