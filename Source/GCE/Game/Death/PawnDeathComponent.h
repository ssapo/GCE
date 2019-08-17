// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Death/ChessDeathComponent.h"
#include "PawnDeathComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UPawnDeathComponent : public UChessDeathComponent
{
	GENERATED_BODY()
	
public:
	UPawnDeathComponent();
};
