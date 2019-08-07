// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessCameraPawn.h"
#include <Camera/CameraComponent.h>

// Sets default values
AChessCameraPawn::AChessCameraPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocationAndRotation(FVector(700.0f, 0.0f, 700.0f), FRotator(-60.0f, 0.0f, 0.0f));
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

}

void AChessCameraPawn::SetCameraTransform(const FTransform& Transform)
{
	GCE_CHECK(nullptr != CameraComponent);
	//SetActorLocation(Transform.GetLocation());
	CameraComponent->SetRelativeLocation(Transform.GetLocation());
	CameraComponent->SetRelativeRotation(Transform.GetRotation());
}

