// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessDeathComponent.h"

UChessDeathComponent::UChessDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UChessDeathComponent::BeginPlay()
{
	Super::BeginPlay();

	AlreadyDestroyed = false;
}

void UChessDeathComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WillDestroy && !AlreadyDestroyed)
	{
		AlreadyDestroyed = true;
		if (auto Owner = GetOwner())
		{
			Owner->Destroy();
		}
	}
}

void UChessDeathComponent::WillDieItSelf()
{
	WillDestroy = true;
}

EChessClass UChessDeathComponent::GetClass() const
{
	return ChessClass;
}

