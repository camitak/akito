// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/MainCharacterAnimInstance.h"
#include "Character/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if (MainCharacter)
	{
		MainCharacterMovement = MainCharacter->GetCharacterMovement();
	}

}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (MainCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MainCharacterMovement->Velocity);
		IsFalling = MainCharacterMovement->IsFalling();
		bIsCrouching = MainCharacter->IsCrouching();
		FRotator CharacterRotation = MainCharacter->GetActorRotation();
		Direction = CharacterRotation.Yaw;
		CharacterState = MainCharacter->GetCharacterState();
	}
}
