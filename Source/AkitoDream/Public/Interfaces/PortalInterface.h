// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PortalInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPortalInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AKITODREAM_API IPortalInterface
{
	GENERATED_BODY()

public:

	virtual void OpenPortal() = 0;

};
