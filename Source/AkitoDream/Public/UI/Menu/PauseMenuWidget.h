// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class AKITODREAM_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized() override;

protected:
	void Resume();


	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitDesktopButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitMainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* QuitBox;

private:

	
	UFUNCTION()
	void OnResumeButtonPressed();
	
	UFUNCTION()
	void OnOptionsButtonPressed();
	
	UFUNCTION()
	void OnQuitButtonPressed();
	
	UFUNCTION()
	void OnQuitDeskButtonPressed();
	
	UFUNCTION()
	void OnQuitMainMenuButtonPressed();


};
