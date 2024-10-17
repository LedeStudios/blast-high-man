// Copyright Lede Studios. All Rights Reserved.


#include "PlatformBase.h"

#include "PlatformComponent.h"

APlatformBase::APlatformBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformComponent = CreateDefaultSubobject<UPlatformComponent>("PlatformComponent");
}

void APlatformBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlatformBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

