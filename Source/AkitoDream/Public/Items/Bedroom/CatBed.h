// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/InteractItem.h"
#include "CatBed.generated.h"

class APortal;
/**
 * 
 */
UCLASS()
class AKITODREAM_API ACatBed : public AInteractItem
{
	GENERATED_BODY()

public:
	ACatBed();

	virtual void BeginPlay() override;
	virtual void InteractWithItem(AActor* OtherActor) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	APortal* Portal;
		
private:

};
