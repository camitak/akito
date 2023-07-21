// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "UI/Menu/PauseMenuWidget.h"
#include "UI/Menu/GameowerMenuWidget.h"
#include "UI/Menu/EndGameMenuWidget.h"
#include "UI/NPC/NPCWidget.h"
#include "UI/Overlay/OverlayWidget.h"
#include "UI/Overlay/StartWidget.h"

void AMainHUD::BeginPlay()
{
}

void AMainHUD::OpenPauseMenu()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PauseMenuClass = CreateWidget<UPauseMenuWidget>(PlayerController, PauseMenuWidget);
			if (PauseMenuClass)
			{
				OpenMenus(PlayerController, PauseMenuClass);
			}
		}
	}
}

void AMainHUD::OpenGameOverMenu()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			GameOverMenuClass = CreateWidget<UGameowerMenuWidget>(PlayerController, GameOverMenuWidget);
			if (GameOverMenuClass)
			{
				OpenMenus(PlayerController, GameOverMenuClass);
			}
		}
	}
}

void AMainHUD::OpenEndGameMenu()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			EndGameMenuClass = CreateWidget<UEndGameMenuWidget>(PlayerController, EndGameMenuWidget);
			if (EndGameMenuClass)
			{
				OpenMenus(PlayerController, EndGameMenuClass);
			}
		}
	}
}

void AMainHUD::OpenNPCDialog()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			NPCClass = CreateWidget<UNPCWidget>(PlayerController, NPCWidget);
			if (NPCClass)
			{
				OpenDialogs(PlayerController, NPCClass);
			}
		}
	}
}

void AMainHUD::StartOverlay()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			OverlayClass = CreateWidget<UOverlayWidget>(PlayerController, OverlayWidget);
			if (OverlayClass)
			{
				OverlayClass->AddToViewport();
			}
		}
	}
}

void AMainHUD::StartScreen()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			StartClass = CreateWidget<UStartWidget>(PlayerController, StartWidget);
			if (StartClass)
			{
				StartClass->AddToViewport();
			}
		}
	}
}

void AMainHUD::CloseStartScreen()
{
	StartClass->RemoveFromViewport();
}

void AMainHUD::HideOverlay()
{
	if (OverlayClass)
	{
		OverlayClass->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainHUD::ShowOverlay()
{
	if (OverlayClass)
	{
		OverlayClass->SetVisibility(ESlateVisibility::Visible);
	}
}


void AMainHUD::OpenMenus(APlayerController* Controller, UUserWidget* Menu)
{
	Menu->bIsFocusable = true;
	Menu->AddToViewport();

	Controller->SetPause(true);
	Controller->SetShowMouseCursor(true);

	FInputModeUIOnly InputMode;
	TSharedPtr<SWidget> WidgetPtr = Menu->TakeWidget();
	InputMode.SetWidgetToFocus(WidgetPtr);
	Controller->SetInputMode(InputMode);
}

void AMainHUD::OpenDialogs(APlayerController* Controller, UUserWidget* Menu)
{
	Menu->bIsFocusable = true;
	Menu->AddToViewport();

	Controller->SetShowMouseCursor(true);	
}