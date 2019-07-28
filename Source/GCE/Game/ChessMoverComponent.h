// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ChessMoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GCE_API UChessMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChessMoverComponent();

	UFUNCTION(BlueprintCallable)
		void SetCellPoint(const FIntPoint& NewP) { CellPoint = NewP; }

	UFUNCTION(BlueprintCallable)
		void SetCellXY(int32 NewX, int32 NewY) { CellPoint.X = NewX; CellPoint.Y = NewY; }

	UFUNCTION(BlueprintCallable)
		void SetCellX(int32 NewX) { CellPoint.X = NewX; }

	UFUNCTION(BlueprintCallable)
		void SetCellY(int32 NewY) { CellPoint.Y = NewY; }

	UFUNCTION(BlueprintPure)
		FIntPoint GetCell() const { return CellPoint; }

	UFUNCTION(BlueprintPure)
		int32 GetCellX() const { return CellPoint.X; }

	UFUNCTION(BlueprintPure)
		int32 GetCellY() const { return CellPoint.Y; }

private:
	FIntPoint CellPoint;
};
