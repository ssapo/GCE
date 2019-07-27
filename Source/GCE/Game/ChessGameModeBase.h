// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameModeBase.generated.h"

UCLASS()
class GCE_API AChessGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	AChessGameModeBase();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
		TArray<int32> ChessMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		TMap<EChessActor, UClass*> ChessActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		FVector StartInitializeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		FVector StartIntervalLocation;
};
