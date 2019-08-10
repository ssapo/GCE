// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightMoverComponent.h"

UKnightMoverComponent::UKnightMoverComponent()
{
	MoveDirections = {
		FIntPoint(2, 1),
		FIntPoint(2, -1),
		FIntPoint(-2, 1),
		FIntPoint(-2, -1),
		FIntPoint(1, 2),
		FIntPoint(-1, 2),
		FIntPoint(1, -2),
		FIntPoint(-1, -2)
	};

	AttackDirections = {
		FIntPoint(2, 1),
		FIntPoint(2, -1),
		FIntPoint(-2, 1),
		FIntPoint(-2, -1),
		FIntPoint(1, 2),
		FIntPoint(-1, 2),
		FIntPoint(1, -2),
		FIntPoint(-1, -2)
	};

	bPercistance = false;
	bHasSpecialMove = false;
	bHasTeamDirection = false;
}
