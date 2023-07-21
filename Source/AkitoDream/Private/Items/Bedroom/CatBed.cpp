// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bedroom/CatBed.h"
#include "Items/Item.h"
#include "Portal/Portal.h"
#include "Interfaces/PortalInterface.h"

ACatBed::ACatBed()
{
}

void ACatBed::BeginPlay()
{
	Super::BeginPlay();
}

void ACatBed::InteractWithItem(AActor* OtherActor)
{
	Super::InteractWithItem(OtherActor);
	if(Portal)
	{
		IPortalInterface* PortalInterface = Cast<IPortalInterface>(Portal);
		if (PortalInterface)
		{
			PortalInterface->OpenPortal();
		}
	}
}
