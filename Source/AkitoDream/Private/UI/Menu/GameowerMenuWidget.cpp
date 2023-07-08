// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/GameowerMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UGameowerMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RestartButton->OnClicked.AddUniqueDynamic(this, &UGameowerMenuWidget::OnRestartButtonPressed);

}

void UGameowerMenuWidget::OnRestartButtonPressed()
{
	if (RestartButton)
	{
		Resume();
		UGameplayStatics::OpenLevel(this, FName("Level1"), false);
	}
}
