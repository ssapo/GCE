// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChessFuncs.generated.h"

UCLASS()
class GCE_API UChessFuncs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsEqualTeam(const EChessTeam& Team1, const EChessTeam& Team2);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsBlackTeam(const EChessTeam& Team);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsWhiteTeam(const EChessTeam& Team);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsNoneTeam(const EChessTeam& Team);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static EChessTeam GetOpponentTeam(const EChessTeam& Team);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsEqualClass(const EChessClass& C1, const EChessClass& C2);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsKing(const EChessClass& Class);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsBlackKing(const EChessTeam& Team, const EChessClass& Class);

	UFUNCTION(BlueprintPure, Category = "Chess|Misc")
		static bool IsWhiteKing(const EChessTeam& Team, const EChessClass& Class);
};
