// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/InteractItem.h"
#include "Interfaces/UserInterface.h"
#include "EStates/EStates.h"
#include "SimpleBedroomItem.generated.h"

class UAnimMontage;
class IMontageInterface;

/**
 * 
 */
UCLASS()
class AKITODREAM_API ASimpleBedroomItem : public AInteractItem
{
	GENERATED_BODY()
	
public:

	virtual void InteractWithItem(AActor* OtherActor) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* ItemMontage;

	UPROPERTY(EditAnywhere, Category = "Montages")
	TArray<FName> MontageSections;

private:

	
};
