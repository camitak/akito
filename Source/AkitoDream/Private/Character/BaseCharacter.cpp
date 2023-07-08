// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "UI/MainHUD.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ABaseCharacter::BeginPlay() 
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (InputSystem)
			{
				InputSystem->AddMappingContext(MappingContext, 0);
			}
		}
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Jump);
		EnhancedInputComponent->BindAction(EKeyAction, ETriggerEvent::Triggered, this, &ABaseCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Pause);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Run);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ABaseCharacter::ToggleCrouch);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Attack);
		EnhancedInputComponent->BindAction(DialogAction, ETriggerEvent::Triggered, this, &ABaseCharacter::Dialog);

	}
}

void ABaseCharacter::Jump()
{
	Super::Jump();
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		
	FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(Forward, DirectionValue.X);
	AddMovementInput(Right, DirectionValue.Y);
}

void ABaseCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValues = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisValues.X);
	AddControllerPitchInput(LookAxisValues.Y);
}
	
void ABaseCharacter::EKeyPressed(const FInputActionValue& Value)
{

}
	
void ABaseCharacter::Pause(const FInputActionValue& Value)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
		if (MainHUD)
		{
			MainHUD->OpenPauseMenu();
		}
	}
}

void ABaseCharacter::Run(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}


void ABaseCharacter::ToggleCrouch(const FInputActionValue& Value)
{ 
	bIsCrouching = Value.Get<bool>();
}

void ABaseCharacter::Attack()
{

}

void ABaseCharacter::Dialog(const FInputActionValue& Value)
{
}
