// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessActor.h"
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/MovementComponent.h>
#include "ChessPlayerController.h"
#include "ChessGameModeBase.h"
#include "ChessMoverComponent.h"

// Sets default values
AChessActor::AChessActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GCE_LOG_S(Log);
	PrimaryActorTick.bCanEverTick = true;
	bOutlineEffect = true;
	bEnableSelected = true;
	bVisiblityToggled = true;

	ChessBody = nullptr;
	ChessMover = nullptr;
}

void AChessActor::InitChessActor(class UMeshComponent* Piece, class UChessMoverComponent* Mover)
{
	GCE_CHECK(nullptr != Piece);
	ChessBody = Piece;
	ChessMover = Mover;
}

bool AChessActor::IsValidMover()
{
	return ChessMover != nullptr;
}

void AChessActor::SetIntervalVector(const FVector& Value)
{
	if (ChessMover)
	{
		ChessMover->SetIntervalVector(Value);
	}
}

void AChessActor::SetCellXY(int32 NewX, int32 NewY)
{
	if (ChessMover)
	{
		ChessMover->SetCellXY(NewX, NewY);
	}
}

void AChessActor::SetCellPoint(const FIntPoint& Point)
{
	if (ChessMover)
	{
		ChessMover->SetCellPoint(Point);
	}
}

void AChessActor::SetCellX(int32 NewX)
{
	if (ChessMover)
	{
		ChessMover->SetCellX(NewX);
	}
}

void AChessActor::SetCellY(int32 NewY)
{
	if (ChessMover)
	{
		ChessMover->SetCellY(NewY);
	}
}

TArray<FIntPoint> AChessActor::GetDirections() const
{
	if (ChessMover)
	{
		return ChessMover->GetDirections();
	}

	return TArray<FIntPoint>();
}

FIntPoint AChessActor::GetCell() const
{
	if (ChessMover)
	{
		return ChessMover->GetCell();
	}

	return FIntPoint::NoneValue;
}

int32 AChessActor::GetCellX() const
{
	if (ChessMover)
	{
		return ChessMover->GetCellX();
	}

	return INDEX_NONE;
}

int32 AChessActor::GetCellY() const
{
	if (ChessMover)
	{
		return ChessMover->GetCellY();
	}

	return INDEX_NONE;
}

void AChessActor::SetOutlineEffect(bool bToggle)
{
	if (ChessBody)
	{
		ChessBody->SetRenderCustomDepth(bOutlineEffect && bToggle);
	}
}

bool AChessActor::IsPersistance() const
{
	if (ChessMover)
	{
		return ChessMover->IsPercistance();
	}

	return false;
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

// Called every frame
void AChessActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

