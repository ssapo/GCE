// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Death/ChessDeathComponent.h"
#include "BishopDeathComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UBishopDeathComponent : public UChessDeathComponent
{
	GENERATED_BODY()
	
public:
	UBishopDeathComponent();
};
