// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/Actor.h"
#include "ChessActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedChessActor, class AChessActor* const);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovingEndChessActor, class AChessActor* const);

UCLASS()
class GCE_API AChessActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessActor();

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnter(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchLeave(const ETouchIndex::Type FingerIndex) override;
	
	UFUNCTION(BlueprintCallable)
		void SetOutlineEffect(bool bToggle);

	UFUNCTION(BlueprintCallable)
		void SetVisiblity(bool bToggle);

	UFUNCTION(BlueprintPure)
		FORCEINLINE	bool GetVisiblity() const;

	UFUNCTION(BlueprintPure)
		FORCEINLINE	EChessTeam GetTeam() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "ChessPiece")
		void InitChessActor(class UMeshComponent* Piece);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	FOnSelectedChessActor OnSelected;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		class UMeshComponent* ChessBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessTeam", Meta = (AllowPrivateAccess = true))
		EChessTeam ChessTeamType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessTeam", Meta = (AllowPrivateAccess = true))
		EChessActor ChessPieceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		bool bOutlineEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		bool bEnableSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		bool bVisiblityToggled;
};
