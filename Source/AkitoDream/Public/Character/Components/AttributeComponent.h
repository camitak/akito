// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AKITODREAM_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReceiveDamage(float Damage);
	void AddSouls(int32 NumberOfSouls);
	void AddMeows(int32 AmountOfMeow);
	float GetHealthPercent();
	bool IsAlive();

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Meows;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Souls;

public:

	FORCEINLINE int32 GetMeows() const { return Meows; }
	FORCEINLINE int32 GetSouls() const { return Souls; }
};
