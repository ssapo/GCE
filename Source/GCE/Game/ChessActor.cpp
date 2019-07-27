// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessActor.h"
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/MovementComponent.h>
#include "ChessPlayerController.h"

// Sets default values
AChessActor::AChessActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GCE_LOG_S(Log);
	PrimaryActorTick.bCanEverTick = true;
	bOutlineEffect = true;
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

// Called when the game starts or when spawned
void AChessActor::BeginPlay()
{
	GCE_LOG_S(Log);
	Super::BeginPlay();
}

void AChessActor::NotifyActorOnClicked(FKey ButtonPressed)
{
	GCE_LOG(Log, TEXT("Name [%s] Key [%s]"), *GetName(), *ButtonPressed.ToString());
	Super::NotifyActorOnClicked(ButtonPressed);

	if (AChessPlayerController* PC = AChessPlayerController::GetLocalPC())
	{
		PC->ChangeCurrentClickedActor(this);
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

