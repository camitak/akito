// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal/Portal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Interfaces/UserInterface.h"
#include "EStates/EStates.h"
#include "Kismet/GameplayStatics.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	RootComponent = PortalMesh;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());

	PortalBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalBox"));
	PortalBox->SetupAttachment(GetRootComponent());
//	PortalBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PortalBox->SetGenerateOverlapEvents(true);

	PortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));
	PortalEffect->SetupAttachment(GetRootComponent());
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	DeactivatePortalEffect();
	
	PortalBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APortal::OnBoxBeginOverlap);
	PortalBox->OnComponentEndOverlap.AddUniqueDynamic(this, &APortal::OnBoxEndOverlap);
}

void APortal::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bPortalActive)
	{
		IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
		if (UserInterface)
		{
			UserInterface->SetOverlappingItem(this);
		}
	}
}

void APortal::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bPortalActive)
	{
		IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
		if (UserInterface)
		{
			ECharacterWorld CWorld = UserInterface->GetCharacterWorld();
			if (CWorld == ECharacterWorld::ECW_Reality)
			{
				UserInterface->SetCharacterWorld(ECharacterWorld::ECW_Dream);
			}
			else
			{
				UserInterface->SetCharacterWorld(ECharacterWorld::ECW_Reality);
			}
			ClosePortal();
		}
	}
}

void APortal::ActivatePortalEffect()
{
	if (PortalEffect)
	{
		PortalEffect->Activate();
		bPortalActive = true;
		DoorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	}
}

void APortal::DeactivatePortalEffect()
{
	if (PortalEffect)
	{
		PortalEffect->Deactivate();
		bPortalActive = false;
		DoorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	}
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OpenPortal()
{
	ActivatePortalEffect();
	PortalState = EPortalState::EPS_Opened;
}

void APortal::ClosePortal()
{
	DeactivatePortalEffect();
	PortalState = EPortalState::EPS_Closed;
}

void APortal::LoadNewLevel()
{
	FString LevelName = TEXT("Cave");
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}