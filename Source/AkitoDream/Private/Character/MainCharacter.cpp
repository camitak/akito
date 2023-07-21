// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "Character/BaseCharacter.h"
#include "Character/Components/AttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimMontage.h"
#include "Interfaces/InteractInterface.h"
#include "Interfaces/NPCInterface.h"
#include "UI/MainHUD.h"
#include "UI/Overlay/OverlayWidget.h"
#include "Items/Pickup/Soul.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	InitializeCamera();
}

void AMainCharacter::InitializeCamera()
{
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	ArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(ArmComponent);
}

void AMainCharacter::SetCharacterSkin()
{
	if (GetCharacterWorld() == ECharacterWorld::ECW_Dream)
	{
		GetMesh()->SetMaterial(0, DreamMaterial);
	}
	else
	{
		GetMesh()->SetMaterial(0, RealityMaterial);
	}
}

void AMainCharacter::StartCharacterOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
		if (MainHUD)
		{
			MainHUD->StartOverlay();
			OverlayWidget = MainHUD->GetCharacterOverlay();
			if (OverlayWidget && Attributes)
			{
				OverlayWidget->SetHealthBarPercent(Attributes->GetHealthPercent());
				OverlayWidget->SetMeows(0);
				OverlayWidget->SetSouls(0);
			}
		}
	}
}

void AMainCharacter::StartScreen()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
		if (MainHUD)
		{
			MainHUD->StartScreen();
		}
	}
}

void AMainCharacter::CloseStartScreen()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
		if (MainHUD)
		{
			MainHUD->CloseStartScreen();
		}
	}
}

void AMainCharacter::SetHUDHealth()
{
	if (OverlayWidget && Attributes)
	{
		OverlayWidget->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void AMainCharacter::OpenGameOverMenu()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
		if (MainHUD)
		{
			MainHUD->OpenGameOverMenu();
		}
	}
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay(); 
	Tags.Add(FName("EngageableTarget"));
	EquipWeapon();
	StartScreen();
}

void AMainCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	CharacterState = ECharacterState::ECS_Dead;
	DisableMeshCollision();
	OpenGameOverMenu();
}

void AMainCharacter::InteractEnd()
{
	CharacterState = ECharacterState::ECS_Idle;

}

void AMainCharacter::HitReactEnd()
{
	CharacterState = ECharacterState::ECS_Idle;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainCharacter::SetOverlappingItem(AActor* Item)
{
	OverlappingItem = Item;
}

void AMainCharacter::SetCharacterWorld(ECharacterWorld CWorld)
{
	CharacterWorld = CWorld;
	SetCharacterSkin();
	CloseStartScreen();
	StartCharacterOverlay();
}

ECharacterWorld AMainCharacter::GetCharacterWorld()
{
	return CharacterWorld;
}

USceneComponent* AMainCharacter::GetUserMesh()
{
	return this->GetMesh();
}

void AMainCharacter::EKeyPressed(const FInputActionValue& Value)
{
	Super::EKeyPressed(Value);
	

	if (CanInteract())
	{
		IInteractInterface* InteractInterface = nullptr;
		IInteractInterface* TotemInterface = nullptr;
		INPCInterface* NPCInterface = Cast<INPCInterface>(OverlappingItem);

		if (HoldingItem)
		{
			InteractInterface = Cast<IInteractInterface>(HoldingItem);
			if (TotemOverlapping)
			{
				TotemInterface = Cast<IInteractInterface>(TotemOverlapping);
			}
		}
		else
		{
			InteractInterface = Cast<IInteractInterface>(OverlappingItem);
		}
			
		if (InteractInterface)
		{
			if (TotemInterface)
			{
				TotemInterface->InteractWithItem(this);
			}
			InteractInterface->InteractWithItem(this);
		}
		else if (NPCInterface)
		{
			NPCInterface->ActivateDialog();
		}	
	}
}

void AMainCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && OverlayWidget)
	{
		Attributes->AddSouls(Soul->GetSouls());
		OverlayWidget->SetSouls(Attributes->GetSouls());
	}
}

void AMainCharacter::AddMeows(APickupItem* Item)
{
	if (Attributes && OverlayWidget)
	{
		Attributes->AddMeows(Item->GetMeow());
		OverlayWidget->SetMeows(Attributes->GetMeows());
	}
}

void AMainCharacter::RestoreHealth(float HealValue)
{
	if(Attributes)
	{
		Attributes->AddHealth(HealValue);
		OverlayWidget->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

bool AMainCharacter::CanInteract()
{
	return (OverlappingItem || HoldingItem) && 
		(GetCharacterState() == ECharacterState::ECS_Idle || 
		 GetCharacterState() == ECharacterState::ECS_HoldingItem ||
		 GetCharacterState() == ECharacterState::ECS_HoldingInteractable);
}

bool AMainCharacter::IsUnoccupied()
{
	return CharacterState == ECharacterState::ECS_Idle;
}

void AMainCharacter::PlayMontage(UAnimMontage* Montage, TArray<FName>& SectionNames)
{
	if (SectionNames.Num() <= 0) return;
	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionNames[Selection], Montage);
	}
}

void AMainCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);

	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		CharacterState = ECharacterState::ECS_HitReaction;
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	if (CharacterState == ECharacterState::ECS_Dead) return;

	Super::Move(Value);
}

void AMainCharacter::Jump()
{
	if (IsUnoccupied())
	{
		Super::Jump();
	}
}

void AMainCharacter::ReturnToPosition(AActor* Target)
{
	if (Target)
	{
		const FVector Location = Target->GetActorLocation();
		this->SetActorLocation(Location);
	}
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
}
