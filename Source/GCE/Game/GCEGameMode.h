// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/GameMode.h"
#include "GCEGameMode.generated.h"

UCLASS()
class GCE_API AGCEGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGCEGameMode();

	virtual void Tick(float DeltaSeconds) override;

private:
};
