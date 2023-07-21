// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPC.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/UserInterface.h"
#include "NPC/NPCAIController.h"
#include "UI/MainHUD.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());

	EButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EButtonText"));
	EButtonWidget->SetupAttachment(GetRootComponent());
	EButtonWidget->SetVisibility(false);
}

void ANPC::ShowOverlay()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = Cast<APlayerController>(World->GetFirstPlayerController());
		if (PlayerController)
		{
			AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
			if (MainHUD)
			{
				MainHUD->ShowOverlay();
			}
		}
	}
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANPC::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ANPC::OnBoxEndOverlap);
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::ActivateDialog()
{
	SetCamera();
	OpenDialogWidget();
	MyBPEvent();
}

void ANPC::SetCamera()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->SetViewTargetWithBlend(this, 2.f);
		}
	}
}

void ANPC::OpenDialogWidget()
{
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = Cast<APlayerController>(World->GetFirstPlayerController());
		if (PlayerController)
		{
			AMainHUD* MainHUD = Cast<AMainHUD>(PlayerController->GetHUD());
			if (MainHUD)
			{
				MainHUD->OpenNPCDialog();
				MainHUD->HideOverlay();
				HidePressEText();
			}
		}
	}
}

void ANPC::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		IUserInterface* OverlapInterface = Cast<IUserInterface>(OtherActor);
		if (OverlapInterface)
		{
			ShowPressEText();
			OverlapInterface->SetOverlappingItem(this);
		}
	}
}

void ANPC::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		IUserInterface* OverlapInterface = Cast<IUserInterface>(OtherActor);
		if (OverlapInterface)
		{
			HidePressEText();
			OverlapInterface->SetOverlappingItem(nullptr);
		}
	}
}

void ANPC::ShowPressEText()
{
	EButtonWidget->SetVisibility(true);
}

void ANPC::HidePressEText()
{
	EButtonWidget->SetVisibility(false);
}