// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Overlay/OverlayWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UOverlayWidget::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UOverlayWidget::SetMeows(int32 Meow)
{
	if (MeowText)
	{
		const FString String = FString::Printf(TEXT("%d"), Meow);
		const FText Text = FText::FromString(String);
		MeowText->SetText(Text);
	}
}

void UOverlayWidget::SetSouls(int32 Souls)
{
	if (Soulstext)
	{
		const FString String = FString::Printf(TEXT("%d"), Souls);
		const FText Text = FText::FromString(String);
		Soulstext->SetText(Text);
	}
}
