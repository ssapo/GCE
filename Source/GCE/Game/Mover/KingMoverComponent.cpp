// Fill out your copyright notice in the Description page of Project Settings.


#include "KingMoverComponent.h"

UKingMoverComponent::UKingMoverComponent()
{
	MoveDirections = {
		FIntPoint(1, 1),
		FIntPoint(-1, 1),
		FIntPoint(-1, -1),
		FIntPoint(1, -1),
		FIntPoint(1, 0),
		FIntPoint(-1, 0),
		FIntPoint(0, 1),
		FIntPoint(0, -1)
	};

	AttackDirections = {
		FIntPoint(1, 1),
		FIntPoint(-1, 1),
		FIntPoint(-1, -1),
		FIntPoint(1, -1),
		FIntPoint(1, 0),
		FIntPoint(-1, 0),
		FIntPoint(0, 1),
		FIntPoint(0, -1)
	};

	bPercistance = false;
	bHasSpecialMove = true;
	bHasTeamDirection = false;
}
