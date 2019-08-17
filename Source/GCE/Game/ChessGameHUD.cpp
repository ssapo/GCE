// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameHUD.h"
#include "Widgets/ChessUserWidget.h"
#include "GCE.h"

void AChessGameHUD::DrawHUD()
{
	Super::DrawHUD();

}

void AChessGameHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto World = GetWorld();
	GCE_CHECK(nullptr != World);

	auto Widget = CreateWidget<UChessUserWidget>(World, InGameWidget);
	GCE_CHECK(nullptr != Widget);

	Widget->AddToViewport();
}
