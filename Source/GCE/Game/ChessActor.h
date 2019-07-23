// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "GameFramework/Actor.h"
#include "ChessActor.generated.h"

UCLASS()
class GCE_API AChessActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "ChessPiece")
		void InitChessPiece(class UMeshComponent* Piece, class UMovementComponent* Movement);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		class UMeshComponent* ChessBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		class UMovementComponent* ChessMove;
};
