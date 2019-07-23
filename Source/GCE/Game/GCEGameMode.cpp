// Fill out your copyright notice in the Description page of Project Settings.


#include "GCEGameMode.h"
#include <LogVerbosity.h>
//#include "GCE_Actor.h"

AGCEGameMode::AGCEGameMode()
{
	GCE_LOG_S(Display);
}

void AGCEGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
