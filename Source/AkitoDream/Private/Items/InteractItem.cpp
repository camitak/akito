// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InteractItem.h"
#include "Components/WidgetComponent.h"

AInteractItem::AInteractItem()
{
	EButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EButtonText"));
	EButtonWidget->SetupAttachment(GetRootComponent());
}

void AInteractItem::InteractWithItem(AActor* OtherActor)
{
	HidePressEText();
}

USceneComponent* AInteractItem::GetItemMesh()
{
	return nullptr;
}

void AInteractItem::BeginPlay()
{
	Super::BeginPlay();
	HidePressEText();
}

void AInteractItem::ShowPressEText()
{
	EButtonWidget->SetVisibility(true);
}

void AInteractItem::HidePressEText()
{
	EButtonWidget->SetVisibility(false);
}

void AInteractItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	ShowPressEText();
}

void AInteractItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	HidePressEText();
}
