// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/GameMode.h"
#include "ChessGameModeBase.generated.h"

UCLASS()
class GCE_API AChessGameMode : public AGameMode
{
	GENERATED_BODY()

public: 
	AChessGameMode();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;
	void OnSelectedChessActor(class AChessActor* const ChessActor);

private:

	UPROPERTY()
		TArray<int32> ChessGameMap;

	UPROPERTY()
		TArray<TWeakObjectPtr<class AChessActor>> ChessMoveMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		UClass* SelectableActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		UClass* ChessBoardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		TMap<EChessActor, UClass*> ChessActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		FVector StartInitializeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		FVector StartIntervalLocation;

	TWeakObjectPtr<class AChessPlayerController> ChessPlayerController;
};
