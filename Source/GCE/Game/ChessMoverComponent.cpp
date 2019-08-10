// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMoverComponent.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UChessMoverComponent::UChessMoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentPoint = FIntPoint::ZeroValue;
	DesiredPosition = FVector::ZeroVector;

	MovementSpeed = 1000.0f;
	bPercistance = false;
	bMoving = false;
}

void UChessMoverComponent::SetCellXY(int32 NewX, int32 NewY)
{
	FVector NewLocation = GetOwner()->GetActorLocation();

	float MomvmentX = (NewX - CurrentPoint.X) * IntervalVector.X;
	float MovementY = (NewY - CurrentPoint.Y) * IntervalVector.Y;
	CurrentPoint.X = NewX;
	CurrentPoint.Y = NewY;

	DesiredPosition = FVector(NewLocation.X + MomvmentX, NewLocation.Y + MovementY, NewLocation.Z);
	bMoving = true;
	//GetOwner()->SetActorLocation(NewLocation);
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

void UChessMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	bFirstMove = true;
}

void UChessMoverComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MoveToDesiredPosition(DeltaTime);
}

void UChessMoverComponent::MoveToDesiredPosition(float DeltaTime)
{
	if (false == bMoving)
	{
		return;
	}

	FVector PrevLocation = GetOwner()->GetActorLocation();
	FVector Dist = (DesiredPosition - PrevLocation);
	FVector Movement = (DeltaTime * Dist.GetSafeNormal() * MovementSpeed);

	if (Dist.Size() <= Movement.Size())
	{
		PrevLocation = DesiredPosition;
		bMoving = false;

		OnMovingEnd.Broadcast(this);
	}
	else
	{
		PrevLocation += Movement;
	}

	GetOwner()->SetActorLocation(PrevLocation);
}
