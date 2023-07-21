// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Bedroom/SimpleBedroomItem.h"
#include "Components/SphereComponent.h"
#include "Interfaces/UserInterface.h"


void ASimpleBedroomItem::InteractWithItem(AActor* OtherActor)
{
    Super::InteractWithItem(OtherActor);

    IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
    if (UserInterface && ItemMontage)
    {
        UserInterface->PlayMontage(ItemMontage, MontageSections);
		UserInterface->SetCharacterState(ECharacterState::ECS_Interacting);
    }	
}