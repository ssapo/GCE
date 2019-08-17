// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Death/ChessDeathComponent.h"
#include "QueenDeathComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UQueenDeathComponent : public UChessDeathComponent
{
	GENERATED_BODY()
	
public:
	UQueenDeathComponent();
};
