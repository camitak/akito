// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Puzzles/FishPuzzle/Basket.h"
#include "Items/Puzzles/FishPuzzle/PuzzlePlatform.h"
#include "Interfaces/InteractInterface.h"
#include "Interfaces/UserInterface.h"
#include "EStates/EStates.h"

void ABasket::BeginPlay()
{
	Super::BeginPlay();
	if (Platform)
	{
		LinkedPlatform = Cast<APuzzlePlatform>(Platform);
	}
}

void ABasket::InteractWithItem(AActor* OtherActor)
{
	if (OtherActor && InteractInterface)
	{
		AttachMeshToSocket(InteractInterface->GetItemMesh(), FName("KeySocket"));
		IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
		if (LinkedPlatform)
		{
			LinkedPlatform->RevealPlatform();
		}
		if (UserInterface)
		{
			UserInterface->SetCharacterState(ECharacterState::ECS_Idle);
			UserInterface->SetHoldingItem(nullptr);
			UserInterface->SetTotem(nullptr);
		}

		InteractInterface = nullptr;
	}
}

void ABasket::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
	if (UserInterface)
	{
		if (UserInterface->GetCharacterState() == ECharacterState::ECS_HoldingItem)
		{
			UserInterface->SetCharacterState(ECharacterState::ECS_HoldingInteractable);
			UserInterface->SetTotem(this);
		}
	}

	if (OtherActor->ActorHasTag(Key))
	{
		InteractInterface = Cast<IInteractInterface>(OtherActor);
	}
}

void ABasket::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
	if (UserInterface)
	{
		if (UserInterface->GetCharacterState() == ECharacterState::ECS_HoldingInteractable)
		{
			UserInterface->SetCharacterState(ECharacterState::ECS_HoldingItem);
			UserInterface->SetTotem(nullptr);
		}
	}

	InteractInterface = nullptr;
}

void ABasket::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	InParent->AttachToComponent(ItemMeshComponent, TransformRules, InSocketName);
}


void ABasket::DetachMeshToSocket()
{
	FDetachmentTransformRules TransformRules(EDetachmentRule::KeepWorld, true);
	ItemMeshComponent->DetachFromComponent(TransformRules);
}

