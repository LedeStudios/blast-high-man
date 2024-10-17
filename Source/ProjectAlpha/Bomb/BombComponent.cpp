// Copyright Lede Studios. All Rights Reserved.


#include "BombComponent.h"

#include "Bomb.h"
#include "BombBase.h"
#include "BombChargeDisplay.h"
#include "BombHolder.h"
#include "Camera/CameraComponent.h"
#include "Player/PA_Character.h"


UBombComponent::UBombComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UBombComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = CastChecked<APA_Character>(GetOwner());
	
	BombSpawnerProperty.BombHolder = NewObject<UBombHolder>(this);
	BombSpawnerProperty.CurrentBombEnergy = BombSpawnerProperty.InitBombEnergy;
}

void UBombComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsAnyBombCharging()) {
		// Update Charge Level
		BombChargerProperty.ChargeLevel = BombChargerProperty.CurrentChargeMs / BombChargerProperty.ChargeSpeedMsPerLevel;
		if (BombChargerProperty.ChargeLevel < BombChargerProperty.MaxChargeLevel)
		{
			BombChargerProperty.CurrentChargeMs += (DeltaTime * 1000);
		}

		// Set Charge Level to Spawned Charge Actor
		if (BombSpawnerProperty.SpawnedBombChargeActor)
		{
			BombSpawnerProperty.SpawnedBombChargeActor->SetChargeLevel(BombChargerProperty.ChargeLevel);
		}
	}

	if (BombSpawnerProperty.SpawnedBombChargeActor)
	{
		BombSpawnerProperty.SpawnedBombChargeActor->SetActorLocation(GetBombSpawnLoc());
	}
}

int32 UBombComponent::GetChargeLevel() const
{
	return BombChargerProperty.ChargeLevel;
}

void UBombComponent::Charge(const EBombType Type)
{
	// 보유중인 에너지가 폭탄 발사에 필요한 에너지보다 적으면 차지 중지
	if (BombSpawnerProperty.CurrentBombEnergy < BombSpawnerProperty.EnergyToUse)
	{
		return;
	}
	
	if (!IsAnyBombCharging())
	{
		Type == EBombType::Attraction
		? BombChargerProperty.bIsAttractionCharge = true
		: BombChargerProperty.bIsRepulsionCharge = true;

		Spawn(Type);
	}
}

void UBombComponent::EndCharge()
{
	if (BombChargerProperty.bIsAttractionCharge)
	{
		Shoot(EBombType::Attraction);
	}

	if (BombChargerProperty.bIsRepulsionCharge)
	{
		Shoot(EBombType::Repulsion);
	}

	BombChargerProperty.ChargeLevel = 0;
	BombChargerProperty.CurrentChargeMs = 0;
	BombChargerProperty.bIsAttractionCharge = false;
	BombChargerProperty.bIsRepulsionCharge = false;
}

bool UBombComponent::IsAnyBombCharging() const
{
	return BombChargerProperty.bIsAttractionCharge || BombChargerProperty.bIsRepulsionCharge;
}

bool UBombComponent::IsBombCharging(const EBombType Type) const
{
	return Type == EBombType::Attraction ? BombChargerProperty.bIsAttractionCharge : BombChargerProperty.bIsRepulsionCharge;
}

void UBombComponent::Spawn(const EBombType Type)
{
	// 보유중인 에너지가 폭탄 발사에 필요한 에너지보다 적으면 스폰 중지
	if (BombSpawnerProperty.CurrentBombEnergy < BombSpawnerProperty.EnergyToUse)
	{
		return;
	}

	// 보유중인 에너지 감소
	BombSpawnerProperty.CurrentBombEnergy -= BombSpawnerProperty.EnergyToUse;

	// 폭탄 소환 및 소켓에 부착
	const FActorSpawnParameters Params;
	
	BombSpawnerProperty.SpawnedBombChargeActor = GetWorld()->SpawnActor<ABombChargeDisplay>(
		BombSpawnerProperty.BombChargeActorClass, GetBombSpawnLoc(), FRotator::ZeroRotator, Params);
	
	BombSpawnerProperty.SpawnedBombChargeActor->SetActorRelativeScale3D(FVector(0.1));
	BombSpawnerProperty.SpawnedBombChargeActor->SetBombType(Type);
}

void UBombComponent::Shoot(const EBombType Type)
{
	// 차징중인 폭탄 제거
	if (BombSpawnerProperty.SpawnedBombChargeActor)
	{
		BombSpawnerProperty.SpawnedBombChargeActor->Destroy();
	}

	const FActorSpawnParameters Params;
	ABombBase* Bomb = GetWorld()->SpawnActor<ABombBase>(BombSpawnerProperty.BombClass, GetBombSpawnLoc(), FRotator::ZeroRotator, Params);

	const UCameraComponent* Camera = PlayerCharacter->GetFPCamera();
	Bomb->SetLaunchVelocity(Camera->GetForwardVector() * 1000);
	Bomb->SetBombType(Type);

	BombSpawnerProperty.BombHolder->AddLast(Bomb);
}

void UBombComponent::Clear() const
{
	if (BombSpawnerProperty.BombHolder)
	{
		BombSpawnerProperty.BombHolder->Clear();
	}

	if (BombSpawnerProperty.SpawnedBombChargeActor)
	{
		BombSpawnerProperty.SpawnedBombChargeActor->Destroy();
	}
}

void UBombComponent::SetBombEnergy(const int32 InBombEnergy)
{
	BombSpawnerProperty.CurrentBombEnergy = InBombEnergy;
}

FVector UBombComponent::GetBombSpawnLoc() const
{
	if (PlayerCharacter.IsValid())
	{
		if (const UCameraComponent* Camera = PlayerCharacter->GetFPCamera())
		{
			return Camera->GetComponentLocation() + Camera->GetForwardVector() * 200;
		}
	}
	return FVector::Zero();
}

