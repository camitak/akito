#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/UserInterface.h"
#include "Character/DamageableCharacter.h"
#include "EStates/EStates.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UMaterialInterface;
class UCameraComponent;
class UOverlayWidget;
class UAnimMontage;
class APickupItem;
class ASoul;

UCLASS()
class AKITODREAM_API AMainCharacter : public ADamageableCharacter, public IUserInterface
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetOverlappingItem(AActor* Item) override;
	virtual void SetCharacterWorld(ECharacterWorld CWorld) override;
	virtual void EKeyPressed(const FInputActionValue& Value) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddMeows(APickupItem* Item) override;
	virtual void PlayMontage(UAnimMontage* Montage, TArray<FName>& SectionNames) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Jump() override;
	virtual void ReturnToPosition(AActor* Target) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual ECharacterWorld GetCharacterWorld() override;
	virtual USceneComponent* GetUserMesh() override;

protected:
	virtual void BeginPlay() override;
	virtual void Die_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void InteractEnd();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* ArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Skin")
	UMaterialInterface* DreamMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Skin")
	UMaterialInterface* RealityMaterial;


private:	
	void InitializeCamera();
	void SetCharacterSkin();
	void StartCharacterOverlay();
	void StartScreen();
	void CloseStartScreen();
	void SetHUDHealth();
	void OpenGameOverMenu();
	bool CanInteract();
	bool IsUnoccupied();

	UPROPERTY(VisibleAnywhere, Category = States)
	AActor* OverlappingItem;

	UPROPERTY(VisibleAnywhere, Category = States)
	AActor* HoldingItem;

	UPROPERTY(VisibleAnywhere, Category = States)
	AActor* TotemOverlapping;

	FVector Destination;
	UOverlayWidget* OverlayWidget;

public:
	FORCEINLINE ECharacterState GetCharacterState() { return CharacterState; }
	FORCEINLINE void SetCharacterState(ECharacterState NewState) { CharacterState = NewState; }
	FORCEINLINE void SetHoldingItem(AActor* Item) { HoldingItem = Item; }
	FORCEINLINE void SetTotem(AActor* NewTotem) { TotemOverlapping = NewTotem; }
};
