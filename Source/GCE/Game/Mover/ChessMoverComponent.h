// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "Components/ActorComponent.h"
#include "ChessMoverComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovingEnd, UChessMoverComponent* const);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UChessMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChessMoverComponent();

	UFUNCTION(BlueprintCallable)
		void SetCellPoint(const FIntPoint& NewP, bool NeedAnim = true);

	UFUNCTION(BlueprintCallable)
		void SetCell(int32 NewX, int32 NewY, bool NeedAnim = true);

	UFUNCTION(BlueprintCallable)
		void SetCellX(int32 NewX, bool NeedAnim = true);

	UFUNCTION(BlueprintCallable)
		void SetCellY(int32 NewY, bool NeedAnim = true);

	UFUNCTION(BlueprintCallable)
		void SetIntervalVector(const FVector& Value) { IntervalVector = Value; }

	UFUNCTION(BlueprintPure)
		TArray<FIntPoint> GetMoveDirections() const { return MoveDirections; }

	UFUNCTION(BlueprintPure)
		TArray<FIntPoint> GetAttackDirections() const { return AttackDirections; }

	UFUNCTION(BlueprintPure)
		FIntPoint GetCell() const { return CurrentPoint; }

	UFUNCTION(BlueprintPure)
		int32 GetCellX() const { return CurrentPoint.X; }

	UFUNCTION(BlueprintPure)
		int32 GetCellY() const { return CurrentPoint.Y; }

	UFUNCTION(BlueprintPure)
		bool IsPercistance() const { return bPercistance; }

	UFUNCTION(BlueprintCallable)
		void SetFirstMove(bool Value) { bChessFirstMove = Value; }

	UFUNCTION(BlueprintPure)
		bool IsFirstMove() const { return bChessFirstMove; }

	UFUNCTION(BlueprintPure)
		bool HasSpecialMove() const { return bHasSpecialMove; }

	UFUNCTION(BlueprintPure)
		bool HasTeamDirection() const { return bHasTeamDirection; }

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	virtual bool InintializeBeginPlay();
	void MoveToDesiredPosition(float DeltaTime);

public:
	FOnMovingEnd OnMovingEnd;

protected:
	FIntPoint CurrentPoint;

	FVector IntervalVector;

	FVector DesiredPosition;

	float MovementSpeed;

	bool bMoving;

	bool bChessFirstMove;

	bool bInitializedMove;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction", Meta = (AllowPrivateAccess = true))
		TArray<FIntPoint> MoveDirections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction", Meta = (AllowPrivateAccess = true))
		TArray<FIntPoint> AttackDirections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direction", Meta = (AllowPrivateAccess = true))
		bool bPercistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", Meta = (AllowPrivateAccess = true))
		bool bHasSpecialMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", Meta = (AllowPrivateAccess = true))
		bool bHasTeamDirection;
};