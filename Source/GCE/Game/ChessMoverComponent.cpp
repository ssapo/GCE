// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoverComponent.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UChessMoverComponent::UChessMoverComponent()
{
	CurrentPoint = FIntPoint::ZeroValue;

	bPercistance = false;
}

void UChessMoverComponent::SetCellXY(int32 NewX, int32 NewY)
{
	FVector NewLocation = GetOwner()->GetActorLocation();

	float MomvmentX = (NewX - CurrentPoint.X) * IntervalVector.X;
	float MovementY = (NewY - CurrentPoint.Y) * IntervalVector.Y;
	CurrentPoint.X = NewX;
	CurrentPoint.Y = NewY;

	NewLocation = FVector(NewLocation.X + MomvmentX, NewLocation.Y + MovementY, NewLocation.Z);
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
