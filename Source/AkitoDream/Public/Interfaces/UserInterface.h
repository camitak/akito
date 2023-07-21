// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EStates/EStates.h"
#include "UserInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUserInterface : public UInterface
{
	GENERATED_BODY()
};


class ASoul;
class APickupItem;
/**
 * 
 */
class AKITODREAM_API IUserInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetOverlappingItem(AActor* Item) = 0;
	virtual void SetHoldingItem(AActor* Item) = 0;
	virtual void SetTotem(AActor* NewTotem) = 0;
	virtual void SetCharacterWorld(ECharacterWorld CWorld) = 0;
	virtual void SetCharacterState(ECharacterState NewState) = 0;
	virtual void PlayMontage(UAnimMontage* Montage, TArray<FName>& SectionNames) = 0;
	virtual void AddSouls(ASoul* Soul) = 0;
	virtual void AddMeows(APickupItem* Item) = 0;
	virtual void RestoreHealth(float HealValue) = 0;
	virtual void ReturnToPosition(AActor* Target) = 0;
	virtual ECharacterWorld GetCharacterWorld() = 0;
	virtual ECharacterState GetCharacterState() = 0;
	virtual USceneComponent* GetUserMesh() = 0;
};
