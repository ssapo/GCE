// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Death/ChessDeathComponent.h"
#include "KingDeathComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UKingDeathComponent : public UChessDeathComponent
{
	GENERATED_BODY()
	
public:
	UKingDeathComponent();
};
