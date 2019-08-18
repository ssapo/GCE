// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Widgets/ChessUserWidget.h"
#include "SlateDelegates.h"
#include "UniformStyleButton.generated.h"

UCLASS()
class GCE_API UUniformStyleButton : public UChessUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

	void RegistClickDelegate(const FScriptDelegate& Delegate);
	void RemoveClickDelegate();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		FText InText;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* InTextBlock;

	UPROPERTY(meta = (BindWidget))
		class UButton* InButton;
};
