// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EStates/EStates.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class USceneComponent;

/**
 * 
 */
class AKITODREAM_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void InteractWithItem(AActor* OtherActor) = 0;
	virtual EItemState GetItemState() = 0;
	virtual void SetItemState(EItemState NewState) = 0;
	virtual USceneComponent* GetItemMesh() = 0;
};
