// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCE.h"
#include "Components/ActorComponent.h"
#include "ChessDeathComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GCE_API UChessDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UChessDeathComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void WillDieItSelf();

	UFUNCTION(BlueprintPure)
		EChessClass GetClass() const;

protected:
	bool WillDestroy;
	bool AlreadyDestroyed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EChessClass ChessClass;
};
