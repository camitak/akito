// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "EStates/EStates.h"
#include "Interfaces/HitInterface.h"
#include "DamageableCharacter.generated.h"

class UAttributeComponent;
class UAnimMontage;
class AWeapon;

/**
 * 
 */
UCLASS()
class AKITODREAM_API ADamageableCharacter : public ABaseCharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ADamageableCharacter();
	
protected:

	virtual void Attack() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void HandleDamage(float DamageAmount);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
	virtual bool CanAttack();
	virtual int32 PlayDeathMontage();

	void EquipWeapon();
	void DirectionalHitReact(const FVector& ImpactPoint);
	void PlayHitReactMontage(const FName& SectionName);
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	void DisableMeshCollision();
	void DisableCapsule();
	void StopAttackMontage();
	bool IsAlive();
	int32 PlayMontageCombat(UAnimMontage* Montage, TArray<FName>& SectionNames);
	
	UFUNCTION(BlueprintNativeEvent)
	void Die();

	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* Attributes;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere, Category = Combat)
	double WarpTargetDistance = 75.f;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TArray<FName> AttackSections;

	UPROPERTY(VisibleAnywhere, Category = States)
	ECharacterWorld CharacterWorld = ECharacterWorld::ECW_Reality;
	
	UPROPERTY(VisibleAnywhere, Category = States)
	ECharacterState CharacterState = ECharacterState::ECS_Idle;

private:

	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

public:
	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return DeathPose; }
};
