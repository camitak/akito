// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/InteractItem.h"
#include "EStates/EStates.h"
#include "Fish.generated.h"

class UAnimMontage;
class USceneComponent;

/**
 * 
 */
UCLASS()
class AKITODREAM_API AFish : public AInteractItem
{
	GENERATED_BODY()

public:
	virtual void InteractWithItem(AActor* OtherActor) override;
	virtual USceneComponent* GetItemMesh() override;

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	void DetachMeshToSocket();
	

protected:

	UPROPERTY(EditAnywhere)
	UAnimMontage* PickDropMontage;

	UPROPERTY(EditAnywhere)
	TArray<FName> MontageSections;

private:


};
