// Fill out your copyright notice in the Description page of Project Settings.

#include "ChessFuncs.h"
#include "ChessActor.h"
#include "ChessPlayerController.h"

bool UChessFuncs::IsEqualTeam(const EChessTeam& Team1, const EChessTeam& Team2)
{
	return (Team1 == Team2);
}

bool UChessFuncs::IsBlackTeam(const EChessTeam& Team)
{
	return IsEqualTeam(EChessTeam::Black, Team);
}

bool UChessFuncs::IsWhiteTeam(const EChessTeam& Team)
{
	return IsEqualTeam(EChessTeam::White, Team);
}
