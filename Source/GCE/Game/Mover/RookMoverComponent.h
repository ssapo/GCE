// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Mover/ChessMoverComponent.h"
#include "RookMoverComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API URookMoverComponent : public UChessMoverComponent
{
	GENERATED_BODY()
	
public:
	URookMoverComponent();
};
