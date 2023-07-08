// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class AKITODREAM_API UOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthBarPercent(float Percent);
	void SetMeows(int32 Meow);
	void SetSouls(int32 Souls);

protected:

private:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MeowText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Soulstext;

};
