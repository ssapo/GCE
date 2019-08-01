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

public:
	UFUNCTION(BlueprintCallable)
		void ChangeCurrentClickedActor(class AChessActor* ClickedActor);
	
	UFUNCTION(BlueprintPure)
		class AChessActor* GetCurrentClickedActor() const;

	UFUNCTION(BlueprintCallable)
		void SetChoosenChessTeam(const EChessTeam& Team) { ChoosenChessTeam = Team; }

	UFUNCTION(BlueprintPure)
		EChessTeam GetChoosenChessTeam() const { return ChoosenChessTeam; }

private:
	UPROPERTY()
		TWeakObjectPtr<class AChessActor> CurrentClickedActor;

	UPROPERTY()
		EChessTeam ChoosenChessTeam;
};
