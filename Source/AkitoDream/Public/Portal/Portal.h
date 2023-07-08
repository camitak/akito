// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PortalInterface.h"
#include "EStates/EStates.h"
#include "Portal.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UNiagaraComponent;

UCLASS()
class AKITODREAM_API APortal : public AActor, public IPortalInterface
{
	GENERATED_BODY()
	
public:	
	APortal();
	virtual void Tick(float DeltaTime) override;
	virtual void OpenPortal() override;

	void ClosePortal();

	

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = Portal)
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditAnywhere, Category = Portal)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, Category = Portal)
	UBoxComponent* PortalBox;

	UPROPERTY(EditAnywhere, Category = Portal)
	UNiagaraComponent* PortalEffect;

private:	
	
	void ActivatePortalEffect();
	void DeactivatePortalEffect();
	bool bPortalActive = false;
	void LoadNewLevel();

	EPortalState PortalState = EPortalState::EPS_Closed;

};
