// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessActor.h"
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/MovementComponent.h>
#include "ChessPlayerController.h"
#include "ChessGameModeBase.h"

// Sets default values
AChessActor::AChessActor()
{
	bOutlineEffect = true;
	bEnableSelected = true;
	bVisiblityToggled = true;

	ChessBody = nullptr;
}

void AChessActor::InitChessActor(class UMeshComponent* Piece)
{
	GCE_CHECK(nullptr != Piece);
	ChessBody = Piece;
}

void AChessActor::SetOutlineEffect(bool bToggle)
{
	if (ChessBody)
	{
		ChessBody->SetRenderCustomDepth(bOutlineEffect && bToggle);
	}
}

void AChessActor::SetVisiblity(bool bToggle)
{
	if (bVisiblityToggled != bToggle)
	{
		bVisiblityToggled = bToggle;

		if (ChessBody)
		{
			ChessBody->SetVisibility(bVisiblityToggled);
		}
	}
}

// Called when the game starts or when spawned
void AChessActor::BeginPlay()
{
	GCE_LOG_S(Log);
	Super::BeginPlay();
}

void AChessActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	if (bEnableSelected && bVisiblityToggled)
	{
		GCE_LOG(Log, TEXT("Name [%s] Key [%s]"), *GetName(), *ButtonPressed.ToString());
		OnSelected.Broadcast(this);
	}
}

void AChessActor::NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex)
{
	GCE_LOG(Log, TEXT("Name [%s]"), *GetName());
	Super::NotifyActorOnInputTouchBegin(FingerIndex);
}

void AChessActor::NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex)
{
	GCE_LOG(Log, TEXT("Name [%s]"), *GetName());
	Super::NotifyActorOnInputTouchEnd(FingerIndex);
}

void AChessActor::NotifyActorOnInputTouchEnter(const ETouchIndex::Type FingerIndex)
{
	GCE_LOG(Log, TEXT("Name [%s]"), *GetName());
	Super::NotifyActorOnInputTouchEnter(FingerIndex);
}

void AChessActor::NotifyActorOnInputTouchLeave(const ETouchIndex::Type FingerIndex)
{
	GCE_LOG(Log, TEXT("Name [%s]"), *GetName());
	Super::NotifyActorOnInputTouchLeave(FingerIndex);
}