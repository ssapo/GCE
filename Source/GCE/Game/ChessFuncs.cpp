// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessFuncs.h"
#include "ChessActor.h"
#include "ChessPlayerController.h"

bool UChessFuncs::IsEqualTeam(const EChessTeam& Team1, const EChessTeam& Team2)
{
	return (Team1 == Team2);
}

bool UChessFuncs::IsEqualTeamBetweenTwoActors(class AChessActor* Actor1, class AChessActor* Actor2)
{
	if (nullptr == Actor1)
	{
		return false;
	}

	if (nullptr == Actor2)
	{ 
		return false;
	}

	return IsEqualTeam(Actor1->GetChessTeam(), Actor2->GetChessTeam());
}

bool UChessFuncs::IsEqualTeamBetweenActorAndPlayer(class AChessActor* Actor, class AChessPlayerController* Player)
{
	if (nullptr == Actor)
	{
		return false;
	}

	if (nullptr == Player)
	{
		return false;
	}

	return IsEqualTeam(Actor->GetChessTeam(), Player->GetChoosenChessTeam());
}
