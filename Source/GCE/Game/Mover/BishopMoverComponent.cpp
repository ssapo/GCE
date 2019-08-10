// Fill out your copyright notice in the Description page of Project Settings.


#include "BishopMoverComponent.h"

UBishopMoverComponent::UBishopMoverComponent()
{
	MoveDirections = {
		FIntPoint(1, 1),
		FIntPoint(-1, 1),
		FIntPoint(-1, -1),
		FIntPoint(1, -1)
	};

	AttackDirections = {
		FIntPoint(1, 1),
		FIntPoint(-1, 1),
		FIntPoint(-1, -1),
		FIntPoint(1, -1)
	};

	bPercistance = true;
	bHasSpecialMove = false;
	bHasTeamDirection = false;
}
