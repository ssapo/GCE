// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/Actor.h"
#include "ChessActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedChessActor, class AChessActor* const);

UCLASS()
class GCE_API AChessActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnter(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchLeave(const ETouchIndex::Type FingerIndex) override;
	
	UFUNCTION(BlueprintCallable)
		bool IsValidMover();

	UFUNCTION(BlueprintCallable)
		void SetIntervalVector(const FVector& Value);

	UFUNCTION(BlueprintCallable)
		void SetCellXY(int32 NewX, int32 NewY);

	UFUNCTION(BlueprintCallable)
		void SetCellPoint(const FIntPoint& Point);

	UFUNCTION(BlueprintCallable)
		void SetCellX(int32 NewX);

	UFUNCTION(BlueprintCallable)
		void SetCellY(int32 NewY);

	UFUNCTION(BlueprintPure)
		TArray<FIntPoint> GetDirections() const;

	UFUNCTION(BlueprintPure)
		FIntPoint GetCell() const;

	UFUNCTION(BlueprintPure)
		int32 GetCellX() const;

	UFUNCTION(BlueprintPure)
		int32 GetCellY() const;

	UFUNCTION(BlueprintCallable)
		void SetOutlineEffect(bool bToggle);

	UFUNCTION(BlueprintCallable)
		void SetVisiblity(bool bToggle);

	UFUNCTION(BlueprintPure)
		bool GetVisiblity() const { return bVisiblityToggled; }

	UFUNCTION(BlueprintPure)
		EChessTeam GetChessTeam() const { return ChessTeamType; }

	UFUNCTION(BlueprintCallable)
		bool IsPersistance() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "ChessPiece")
		void InitChessActor(class UMeshComponent* Piece, class UChessMoverComponent* Mover);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	FOnSelectedChessActor OnSelected;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		class UMeshComponent* ChessBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		class UChessMoverComponent* ChessMover;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessTeam", Meta = (AllowPrivateAccess = true))
		EChessTeam ChessTeamType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		bool bOutlineEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		bool bEnableSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		bool bVisiblityToggled;
};
