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