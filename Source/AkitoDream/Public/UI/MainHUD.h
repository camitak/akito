// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UPauseMenuWidget;
class UNPCWidget;
class UOverlayWidget;
class UStartWidget;
class UGameowerMenuWidget;
class UEndGameMenuWidget;

/**
 * 
 */
UCLASS()
class AKITODREAM_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void OpenPauseMenu();
	void OpenGameOverMenu();
	void OpenEndGameMenu();
	void OpenNPCDialog();
	void StartOverlay();
	void StartScreen();
	void CloseStartScreen();

	UPROPERTY(EditAnywhere, Category = Menu)
	TSubclassOf<UPauseMenuWidget> PauseMenuWidget;

	UPROPERTY()
	UPauseMenuWidget* PauseMenuClass;

	UPROPERTY(EditAnywhere, Category = Menu)
	TSubclassOf<UGameowerMenuWidget> GameOverMenuWidget;

	UPROPERTY()
	UGameowerMenuWidget* GameOverMenuClass;

	UPROPERTY(EditAnywhere, Category = Menu)
	TSubclassOf<UEndGameMenuWidget> EndGameMenuWidget;

	UPROPERTY()
	UEndGameMenuWidget* EndGameMenuClass;

	UPROPERTY(EditAnywhere, Category = Menu)
	TSubclassOf<UOverlayWidget> OverlayWidget;

	UPROPERTY()
	UOverlayWidget* OverlayClass;

	UPROPERTY(EditAnywhere, Category = Menu)
	TSubclassOf<UNPCWidget> NPCWidget;

	UPROPERTY()
	UNPCWidget* NPCClass;

	UPROPERTY(EditAnywhere, Category = Menu)
	TSubclassOf<UStartWidget> StartWidget;

	UPROPERTY()
	UStartWidget* StartClass;

protected:



private:
	
	void OpenMenus(APlayerController* Controller, UUserWidget* Menu);
	void OpenDialogs(APlayerController* Controller, UUserWidget* Menu);

public:
	FORCEINLINE UOverlayWidget* GetCharacterOverlay() const { return OverlayClass; }
};
