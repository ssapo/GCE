// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChessMoverComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UChessMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChessMoverComponent();

	UFUNCTION(BlueprintCallable)
		void SetCellPoint(const FIntPoint& NewP);

	UFUNCTION(BlueprintCallable)
		void SetCellXY(int32 NewX, int32 NewY);

	UFUNCTION(BlueprintCallable)
		void SetCellX(int32 NewX);

	UFUNCTION(BlueprintCallable)
		void SetCellY(int32 NewY);

	UFUNCTION(BlueprintCallable)
		void SetIntervalVector(const FVector& Value) { IntervalVector = Value; }

	UFUNCTION(BlueprintPure)
		TArray<FIntPoint> GetDirections() const { return Directions; }

	UFUNCTION(BlueprintPure)
		FIntPoint GetCell() const { return CurrentPoint; }

	UFUNCTION(BlueprintPure)
		int32 GetCellX() const { return CurrentPoint.X; }

	UFUNCTION(BlueprintPure)
		int32 GetCellY() const { return CurrentPoint.Y; }

	UFUNCTION(BlueprintPure)
		bool IsPercistance() const { return bPercistance; }

private:
	FIntPoint CurrentPoint;

	FVector IntervalVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Direction", Meta = (AllowPrivateAccess = true))
		TArray<FIntPoint> Directions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Direction", Meta = (AllowPrivateAccess = true))
		bool bPercistance;
};
