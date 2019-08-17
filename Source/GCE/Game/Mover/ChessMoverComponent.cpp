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
}

void UChessMoverComponent::SetCell(int32 NewX, int32 NewY, bool NeedAnim)
{
	FVector NewPos = GetOwner()->GetActorLocation();

	float MoveX = (NewX - CurrentPoint.X) * IntervalVector.X;
	float MoveY = (NewY - CurrentPoint.Y) * IntervalVector.Y;
	CurrentPoint.X = NewX;
	CurrentPoint.Y = NewY;

	if (NeedAnim)
	{
		bMoving = true;
		DesiredPosition = FVector(NewPos.X + MoveX, NewPos.Y + MoveY, NewPos.Z);
	}
	else
	{
		NewPos.X = MoveX;
		NewPos.Y = MoveY;

		bMoving = false;
		GetOwner()->SetActorLocation(NewPos);
	}
}

void UChessMoverComponent::SetCellPoint(const FIntPoint& NewP, bool NeedAnim)
{
	SetCell(NewP.X, NewP.Y, NeedAnim);
}

void UChessMoverComponent::SetCellX(int32 NewX, bool NeedAnim)
{
	SetCell(NewX, CurrentPoint.Y, NeedAnim);
}

void UChessMoverComponent::SetCellY(int32 NewY, bool NeedAnim)
{
	SetCell(CurrentPoint.X, NewY, NeedAnim);
}

void UChessMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	GCE_CHECK(true == InintializeBeginPlay());
}

bool UChessMoverComponent::InintializeBeginPlay()
{
	bMoving = false;
	bChessFirstMove = true;
	bInitializedMove = true;

	return true;
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
