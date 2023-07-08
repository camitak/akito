// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/PauseMenuWidget.h"
#include "GameowerMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class AKITODREAM_API UGameowerMenuWidget : public UPauseMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

private:

	UFUNCTION()
	void OnRestartButtonPressed();

};
