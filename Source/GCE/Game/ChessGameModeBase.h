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

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

private:
	class AChessActor* GetMoverPieceFromMap(const FIntPoint& Point) const;
	class AChessActor* GetChessPieceFromMap(const FIntPoint& Point) const;
	void SetChessPieceIntoMap(class AChessActor* Actor, const FIntPoint& Point);
	
	void SetVisibleMovableCells(class AChessActor* const ChessActor);
	void SetInvisibleAllCells();

	void OnSelectedChessActor(class AChessActor* const ChessActor);
	void OnMovingEndChessActor(class UChessMoverComponent* const Mover);

	void ProcessClickedMovePiece(class AChessActor* const ChessActor);
	void ProcessClickedChessPiece(class AChessActor* const ChessActor);
	void ProcessPiecesAreSameTeam(class AChessActor* const ChessActor);
	void ProcessPiecesAreOtherTeam(class AChessActor* const ChessActor);

	//Case 1: SameTeam , Current is Null
	void SameTeamCurrentIsNull(class AChessActor* const ChessActor);

	//Case 2: SameTeam , Current is SameTeam
	void SameTeamCurrentIsSameTeam(class AChessActor* const ChessActor);

	//Case 3: SameTeam , Current is OtherTeam
	void SameTeamCurrentIsOtherTeam(class AChessActor* const ChessActor);

	//Case 4: OtherTeam , Current is Null
	void OtherTeamCurrentIsNull(class AChessActor* const ChessActor);

	//Case 5: OtherTeam , Current is SameTeam
	void OtherTeamCurrentIsSameTeam(class AChessActor* const ChessActor);

	//Case 6: OtherTeam , Current is OhterTeam
	void OtherTeamCurrentIsOtherTeam(class AChessActor* const ChessActor);
	
	//Case 7: MovePiece , Current is SameTeam
	void MovePieceCurrentIsSameTeam(class AChessActor* const ChessActor);
	
	//Case 8: MovePiece , Current is OtherTeam
	void MovePieceCurrentIsOtherTeam(class AChessActor* const ChessActor);

private:
	static constexpr int32 CHESS_WIDTH = 8;
	static constexpr int32 CHESS_HEIGHT = 8;

	UPROPERTY()
		TArray<int32> ChessStartMap;

	UPROPERTY()
		TArray<TWeakObjectPtr<class AChessActor>> ChessGameMap;

	UPROPERTY()
		TArray<TWeakObjectPtr<class AChessActor>> ChessMoveMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		UClass* MovePieceClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		UClass* ChessBoardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		TMap<EChessActor, UClass*> ChessActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		FVector StartInitializeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess|Map", Meta = (AllowPrivateAccess = true))
		FVector StartIntervalLocation;

	TWeakObjectPtr<class AChessPlayerController> ChessPlayer;

	bool bWaitAnimation;
};
