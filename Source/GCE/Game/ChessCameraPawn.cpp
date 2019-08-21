// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessCameraPawn.h"
#include <Camera/CameraComponent.h>

// Sets default values
AChessCameraPawn::AChessCameraPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	GCE_CHECK(nullptr != RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	GCE_CHECK(nullptr != CameraComponent);

	CameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AChessCameraPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void AChessCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	CameraComponent->SetRelativeTransform(SetupTransform);
}

void AChessCameraPawn::SetCameraTransform(const FTransform& Transform)
{
	GCE_CHECK(nullptr != CameraComponent);
	CameraComponent->SetWorldTransform(Transform);
}

void AChessCameraPawn::SetCameraMoving(bool bToggleValue)
{

}

