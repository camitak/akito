// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "EStates/EStates.h"
#include "PickupItem.generated.h"

class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class AKITODREAM_API APickupItem : public AItem
{
	GENERATED_BODY()

public:
	APickupItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();

	template<typename T>
	T Avg(T First, T Second);

	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* PickupEffect;

	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Meow;

public:
	FORCEINLINE int32 GetMeow() const { return Meow; }

};

template<typename T>
inline T APickupItem::Avg(T First, T Second)
{
	return T();
}
