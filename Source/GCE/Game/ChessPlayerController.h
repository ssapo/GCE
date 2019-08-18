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

public:
	UFUNCTION(BlueprintCallable)
		void ChangeCurrentClickedActor(class AChessActor* ClickedActor);
	
	UFUNCTION(BlueprintPure) 
		class AChessActor* GetCurrentClickedActor() const;

	UFUNCTION(BlueprintCallable) 
		void SetChoosenChessTeam(const EChessTeam& Team);

	UFUNCTION(BlueprintPure)
		EChessTeam GetChoosenChessTeam() const;

	UFUNCTION(BlueprintPure)
		EChessTeam GetOpponentTeam() const;

	UFUNCTION(BlueprintCallable)
		void SetMyTurn(bool Value);

	UFUNCTION(BlueprintPure)
		bool IsMyTurn() const;

private:
	UPROPERTY()
		TWeakObjectPtr<class AChessActor> CurrentClickedActor;

	UPROPERTY()
		EChessTeam ChoosenChessTeam;

	UPROPERTY()
		bool bMyTurn;
};
