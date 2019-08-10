// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnMoverComponent.h"

UPawnMoverComponent::UPawnMoverComponent()
{
	MoveDirections = {
		FIntPoint(0, 1),
	};

	AttackDirections = {
		FIntPoint(1, 1),
		FIntPoint(-1, 1)
	};

	bPercistance = false;
	bHasSpecialMove = true;
	bHasTeamDirection = true;
}
