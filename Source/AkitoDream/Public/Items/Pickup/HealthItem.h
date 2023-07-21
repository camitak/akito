// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Pickup/PickupItem.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class AKITODREAM_API AHealthItem : public APickupItem
{
	GENERATED_BODY()

public:
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:

	UPROPERTY(EditAnywhere, Category = "Heal")
	float HealValue = 0;

private:

};
