// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/InteractItem.h"
#include "Interfaces/InteractInterface.h"
#include "Basket.generated.h"

class APuzzlePlatform;
class USceneComponent;

/**
 * 
 */
UCLASS()
class AKITODREAM_API ABasket : public AInteractItem
{
	GENERATED_BODY()

public:
	virtual void InteractWithItem(AActor* OtherActor) override;
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
	void DetachMeshToSocket();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APuzzlePlatform* Platform;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	FName Key;

	APuzzlePlatform* LinkedPlatform;
	IInteractInterface* InteractInterface;
	USceneComponent* ItemMesh;

};
