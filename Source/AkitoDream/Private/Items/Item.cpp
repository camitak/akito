// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Interfaces/UserInterface.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMeshComponent;

	ItemSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ItemSphereComponent->SetupAttachment(GetRootComponent());

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	ItemSphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AItem::OnSphereBeginOverlap);
	ItemSphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
	if (UserInterface)
	{
		UserInterface->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
	if (UserInterface)
	{
		UserInterface->SetOverlappingItem(nullptr);
	}
}

