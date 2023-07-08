// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Interfaces/InteractInterface.h"
#include "EStates/EStates.h"
#include "InteractItem.generated.h"

class UTextRenderComponent;
class USceneComponent;

/**
 * 
 */
UCLASS()
class AKITODREAM_API AInteractItem : public AItem, public IInteractInterface
{
	GENERATED_BODY()

public:
	AInteractItem();
	virtual void InteractWithItem(AActor* OtherActor) override;
	virtual USceneComponent* GetItemMesh() override;

	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


protected:
	virtual void BeginPlay() override;

	void ShowPressEText();
	void HidePressEText();

	UPROPERTY(VisibleAnywhere, Category = States)
	EItemState ItemState = EItemState::EIS_None;
	
	UPROPERTY(EditAnywhere, Category = "Interact Propertie")
	class UTextRenderComponent* PressEText;

private:

public:
	FORCEINLINE EItemState GetItemState() { return ItemState; }
	FORCEINLINE void SetItemState(EItemState NewState) { ItemState = NewState; }
};
