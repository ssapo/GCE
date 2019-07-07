// Fill out your copyright notice in the Description page of Project Settings.


#include "GCE_Pawn.h"

// Sets default values
AGCE_Pawn::AGCE_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGCE_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGCE_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGCE_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

