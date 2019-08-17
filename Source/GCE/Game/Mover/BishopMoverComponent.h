// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Mover/ChessMoverComponent.h"
#include "BishopMoverComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UBishopMoverComponent : public UChessMoverComponent
{
	GENERATED_BODY()
	
public:
	UBishopMoverComponent();
};
