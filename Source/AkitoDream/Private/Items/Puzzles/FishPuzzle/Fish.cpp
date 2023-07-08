// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Puzzles/FishPuzzle/Fish.h"
#include "Interfaces/UserInterface.h"
#include "Components/SphereComponent.h"

void AFish::InteractWithItem(AActor* OtherActor)
{
	IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
	if (UserInterface)
	{
		if (UserInterface->GetCharacterState() == ECharacterState::ECS_Idle && ItemState == EItemState::EIS_None)
		{
			UserInterface->SetCharacterState(ECharacterState::ECS_HoldingItem);
			UserInterface->SetHoldingItem(this);
			AttachMeshToSocket(UserInterface->GetUserMesh(), FName("MouthSocket"));
			ItemState = EItemState::EIS_Equipped;
		}
		else if(UserInterface->GetCharacterState() == ECharacterState::ECS_HoldingItem && ItemState == EItemState::EIS_Equipped)
		{
			UserInterface->SetCharacterState(ECharacterState::ECS_Idle);
			UserInterface->SetHoldingItem(nullptr);
			DetachMeshToSocket();
			ItemState = EItemState::EIS_None;
		}
		else
		{
			DetachMeshToSocket();
			ItemState = EItemState::EIS_None;
		}
	}
}

USceneComponent* AFish::GetItemMesh()
{
	return this->GetRootComponent();
}

void AFish::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMeshComponent->AttachToComponent(InParent, TransformRules, InSocketName);
}

void AFish::DetachMeshToSocket()
{
	FDetachmentTransformRules TransformRules(EDetachmentRule::KeepWorld, true);
	ItemMeshComponent->DetachFromComponent(TransformRules);
}

