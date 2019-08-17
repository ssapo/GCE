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

bool UChessFuncs::IsNoneTeam(const EChessTeam& Team)
{
	return IsEqualTeam(EChessTeam::NONE, Team);
}

EChessTeam UChessFuncs::GetOpponentTeam(const EChessTeam& Team)
{
	if (IsWhiteTeam(Team))
	{
		return EChessTeam::White;
	}
	else if (IsBlackTeam(Team))
	{
		return EChessTeam::Black;
	}

	return EChessTeam::NONE;
}

bool UChessFuncs::IsEqualClass(const EChessClass& C1, const EChessClass& C2)
{
	return C1 == C2;
}

bool UChessFuncs::IsKing(const EChessClass& Class)
{
	return IsEqualClass(EChessClass::King, Class);
}

bool UChessFuncs::IsBlackKing(const EChessTeam& Team, const EChessClass& Class)
{
	return IsBlackTeam(Team) && IsKing(Class);
}

bool UChessFuncs::IsWhiteKing(const EChessTeam& Team, const EChessClass& Class)
{
	return IsBlackTeam(Team) && IsKing(Class);
}
