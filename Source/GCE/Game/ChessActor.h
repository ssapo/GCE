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
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnInputTouchBegin(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchEnter(const ETouchIndex::Type FingerIndex) override;
	virtual void NotifyActorOnInputTouchLeave(const ETouchIndex::Type FingerIndex) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "ChessPiece")
		void InitChessActor(class UMeshComponent* Piece);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChessPiece", Meta = (AllowPrivateAccess = true))
		class UMeshComponent* ChessBody;
};
