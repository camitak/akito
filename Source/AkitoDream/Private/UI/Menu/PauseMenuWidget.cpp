// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPauseMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnResumeButtonPressed);
	OptionsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnOptionsButtonPressed);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnQuitButtonPressed);
	QuitDesktopButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnQuitDeskButtonPressed);
	QuitMainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnQuitMainMenuButtonPressed);
}

void UPauseMenuWidget::OnResumeButtonPressed()
{
	Resume();
}

void UPauseMenuWidget::Resume()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();

		if (Controller)
		{
			FInputModeGameOnly InputMode;
			Controller->SetInputMode(InputMode);
			Controller->SetShowMouseCursor(false);
			Controller->SetPause(false);
			RemoveFromParent();
			RemoveFromViewport();
		}
	}
}

void UPauseMenuWidget::OnOptionsButtonPressed()
{
}

void UPauseMenuWidget::OnQuitButtonPressed()
{
	if (QuitBox)
	{
		QuitBox->SetVisibility(ESlateVisibility::Visible);

		if (QuitDesktopButton)
		{
			QuitDesktopButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnQuitDeskButtonPressed);
		}

		if (QuitMainMenuButton)
		{
			QuitMainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnQuitMainMenuButtonPressed);
		}
	}

}

void UPauseMenuWidget::OnQuitDeskButtonPressed()
{
	if (QuitDesktopButton)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);

			if (PlayerController)
			{
				UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, true);
			}

		}

	}
}

void UPauseMenuWidget::OnQuitMainMenuButtonPressed()
{
	if (QuitMainMenuButton)
	{
		Resume();
		UGameplayStatics::OpenLevel(this, FName("Level1"), false);
	}
}
