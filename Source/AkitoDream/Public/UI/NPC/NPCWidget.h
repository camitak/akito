// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class AKITODREAM_API UNPCWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	USizeBox* GetDialogBox();

	UFUNCTION(BlueprintCallable)
	void CloseDialog();

	UPROPERTY(meta = (BindWidget))
	USizeBox* DialogBox;

protected:

private:
};
