// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(GCE, Log, All);

#define GCE_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define GCE_LOG_S(Verbosity) UE_LOG(GCE, Verbosity, TEXT("%s"), *GCE_LOG_CALLINFO)
#define GCE_LOG(Verbosity, Format, ...) UE_LOG(GCE, Verbosity, TEXT("%s%s"), *GCE_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define GCE_CHECK(Expr, ...) { if(!(Expr)) { GCE_LOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }

#define GCE_PRINT(Format, ...) { if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(Format, ##__VA_ARGS__), false, FVector2D::UnitVector); } }

#define GCE_PRINT_C(Color, Format, ...) { if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 3.0f, Color, FString::Printf(Format, ##__VA_ARGS__), false, FVector2D::UnitVector); } }

#define GCE_PRINT_CS(Color, Sec, Format, ...) { if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, Sec, Color, FString::Printf(Format, ##__VA_ARGS__), false, FVector2D::UnitVector); } }

UENUM(BlueprintType)
enum class EChessActor : uint8
{
	NONE			UMETA(DisplayName = "NONE"),
	Marble_Board	UMETA(DisplayName = "Marble Board"),
	White_Pawn		UMETA(DisplayName = "White Pawn"),
	White_Knight	UMETA(DisplayName = "White Knight"),
	White_Rook		UMETA(DisplayName = "White Rook"),
	White_Bishop	UMETA(DisplayName = "White Bishop"),
	White_King		UMETA(DisplayName = "White King"),
	White_Queen		UMETA(DisplayName = "White Queen"),
	Black_Pawn		UMETA(DisplayName = "Black Pawn"),
	Black_Knight	UMETA(DisplayName = "Black Knight"),
	Black_Rook		UMETA(DisplayName = "Black Rook"),
	Black_Bishop	UMETA(DisplayName = "Black Bishop"),
	Black_King		UMETA(DisplayName = "Black King"),
	Black_Queen		UMETA(DisplayName = "Black Queen"),
};


UENUM(BlueprintType)
enum class EChessTeam : uint8
{
	NONE			UMETA(DisplayName = "NONE"),
	White			UMETA(DisplayName = "White"),
	Black			UMETA(DisplayName = "Black"),
};