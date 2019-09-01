// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessDPICustomScalingRule.h"

float UChessDPICustomScalingRule::GetDPIScaleBasedOnSize(FIntPoint Size) const
{
	constexpr int32 SizeX = 1920;
	constexpr int32 SizeY = 1080;

	FIntPoint Point(FMath::Min(SizeX, Size.X), FMath::Min(SizeY, Size.Y));

	return Super::GetDPIScaleBasedOnSize(Point);
}
