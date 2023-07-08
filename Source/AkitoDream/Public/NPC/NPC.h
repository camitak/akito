// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/NPCInterface.h"
#include "NPC.generated.h"

class UBoxComponent;
class UCameraComponent;
class UTextRenderComponent;

UCLASS()
class AKITODREAM_API ANPC : public ACharacter, public INPCInterface
{
	GENERATED_BODY()

public:
	ANPC();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void ActivateDialog() override;

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintImplementableEvent)
	void MyBPEvent();

protected:
	virtual void BeginPlay() override;

private:	
	void ShowPressEText();
	void HidePressEText();
	void SetCamera();
	void OpenDialogWidget();

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Interact Propertie")
	UTextRenderComponent* PressEText;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;


};
