// Fill out your copyright notice in the Description page of Project Settings.


#include "UniformStyleButton.h"
#include "Button.h"
#include "TextBlock.h"
#include "WeakObjectPtr.h"

void UUniformStyleButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	InTextBlock->SetText(InText);
}

void UUniformStyleButton::RegistClickDelegate(const FScriptDelegate& Delegate)
{
	InButton->OnClicked.Add(Delegate);
}

void UUniformStyleButton::RemoveClickDelegate()
{
	InButton->OnClicked.RemoveAll(this);
}
