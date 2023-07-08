// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "Breakable.generated.h"

class UGeometryCollectionComponent;
class UCapsuleComponent;
class APickupItem;

UCLASS()
class AKITODREAM_API ABreakable : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreakable();
	virtual void Tick(float DeltaTime) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;


private:	

	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
	TArray<TSubclassOf<class APickupItem>> TreasureClasses;

	bool bBroken = false;
};
