// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoverComponent.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UChessMoverComponent::UChessMoverComponent()
{
	CurrentPoint = FIntPoint::NoneValue;

	bPercistance = false;
}

void UChessMoverComponent::SetCellXY(int32 NewX, int32 NewY)
{
	FVector NewLocation = GetOwner()->GetActorLocation();

	CurrentPoint.X = NewX;
	CurrentPoint.Y = NewY;
	float MomvmentX = CurrentPoint.X * IntervalVector.X;
	float MovementY = CurrentPoint.Y * IntervalVector.Y;

	NewLocation = FVector(NewLocation.X + MomvmentX, NewLocation.Y + MovementY, 0.0f);
	GetOwner()->SetActorLocation(NewLocation);
}

void UChessMoverComponent::SetCellPoint(const FIntPoint& NewP)
{
	SetCellXY(NewP.X, NewP.Y);
}

void UChessMoverComponent::SetCellX(int32 NewX)
{
	SetCellXY(NewX, CurrentPoint.Y);
}

void UChessMoverComponent::SetCellY(int32 NewY)
{
	SetCellXY(CurrentPoint.X, NewY);
}
