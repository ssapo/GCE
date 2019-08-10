// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/ChessMoverComponent.h"
#include "PawnMoverComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UPawnMoverComponent : public UChessMoverComponent
{
	GENERATED_BODY()

public:
	UPawnMoverComponent();
};
