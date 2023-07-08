#include "Items/Puzzles/FishPuzzle/PuzzlePlatform.h"
#include "Components/BoxComponent.h"
#include "Interfaces/UserInterface.h"

APuzzlePlatform::APuzzlePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(GetRootComponent());
}

void APuzzlePlatform::BeginPlay()
{
	Super::BeginPlay();
	HidePlatform();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APuzzlePlatform::OnBoxOverlap);
}

void APuzzlePlatform::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ReturnTarget)
	{
		IUserInterface* UserInterface = Cast<IUserInterface>(OtherActor);
		if (UserInterface)
		{
			UserInterface->ReturnToPosition(ReturnTarget);
		}
	}
}

void APuzzlePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzlePlatform::RevealPlatform()
{
	MeshComponent->SetVisibility(true);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	MeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void APuzzlePlatform::HidePlatform()
{
	MeshComponent->SetVisibility(false);
	MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

