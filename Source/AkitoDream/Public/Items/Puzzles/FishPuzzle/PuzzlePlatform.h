// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePlatform.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class AKITODREAM_API APuzzlePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzlePlatform();
	virtual void Tick(float DeltaTime) override;

	void RevealPlatform();
	void HidePlatform();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, Category = "Target")
	AActor* ReturnTarget;

private:	

};
