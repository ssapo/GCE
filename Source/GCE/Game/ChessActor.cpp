// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessActor.h"
#include <Engine/StaticMesh.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/MovementComponent.h>

// Sets default values
AChessActor::AChessActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GCE_LOG_S(Display);
	PrimaryActorTick.bCanEverTick = true;
}

void AChessActor::InitChessPiece(class UMeshComponent* Piece, class UMovementComponent* Movement)
{
	GCE_CHECK(nullptr != Piece);
	GCE_CHECK(nullptr != Movement);

	ChessBody = Piece;
	ChessMove = Movement;
}

// Called when the game starts or when spawned
void AChessActor::BeginPlay()
{
	GCE_LOG_S(Display);
	Super::BeginPlay();
}

// Called every frame
void AChessActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

