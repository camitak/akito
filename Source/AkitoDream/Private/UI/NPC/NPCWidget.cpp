// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NPC/NPCWidget.h"

USizeBox* UNPCWidget::GetDialogBox()
{
	return DialogBox;
}

void UNPCWidget::CloseDialog()
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
			RemoveFromParent();
			RemoveFromViewport();
		}
	}
}