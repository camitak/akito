// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class AKITODREAM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void Jump() override;

	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void EKeyPressed(const FInputActionValue& Value);
	virtual void Pause(const FInputActionValue& Value);
	virtual void Run(const FInputActionValue& Value);
	virtual void ToggleCrouch(const FInputActionValue& Value);
	virtual void Attack();
	virtual void Dialog(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EKeyAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DialogAction;

	UPROPERTY(EditAnywhere, Category = "Input|Speed")
	float MaxWalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Input|Speed")
	float MaxRunSpeed = 600.f;

private:	

	bool bIsCrouching = false;

public:

	FORCEINLINE bool IsCrouching() { return bIsCrouching; }

};
