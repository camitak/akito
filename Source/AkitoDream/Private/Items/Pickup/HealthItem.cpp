// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Pickup/HealthItem.h"
#include "Interfaces/UserInterface.h"

void AHealthItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
	if (UserInterface)
	{
		UserInterface->RestoreHealth(HealValue);
	}
}
