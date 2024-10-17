// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BombComponent.generated.h"


class APA_Character;
class ABombBase;
class ABombChargeDisplay;
class UBombSpawner;
class UBombCharger;
class UBombHolder;

UENUM(BlueprintType)
enum class EBombType: uint8
{
	Attraction, Repulsion
};

USTRUCT(BlueprintType)
struct FBombChargerProperty
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0))
	int32 MaxChargeLevel = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0.f))
	int32 ChargeSpeedMsPerLevel = 1500;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentChargeMs = 0;
	
	UPROPERTY(BlueprintReadOnly)
	int32 ChargeLevel = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bIsAttractionCharge = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsRepulsionCharge = false;
};

USTRUCT(BlueprintType)
struct FBombSpawnerProperty
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABombBase> BombClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABombChargeDisplay> BombChargeActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0))
	int32 MaxBombEnergy = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0))
	int32 InitBombEnergy = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin=0))
	int32 EnergyToUse = 10;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentBombEnergy = 0;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBombHolder> BombHolder;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABombChargeDisplay> SpawnedBombChargeActor;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UBombComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBombComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

// ====================================================================================
//  Cache
// ====================================================================================
protected:
	TWeakObjectPtr<APA_Character> PlayerCharacter;
	
// ====================================================================================
//  Bomb Charger
// ====================================================================================
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb")
	FBombChargerProperty BombChargerProperty;

public:
	int32 GetChargeLevel() const;

	void Charge(const EBombType Type);

	void EndCharge();

	bool IsAnyBombCharging() const;

	bool IsBombCharging(const EBombType Type) const;

// ====================================================================================
//  Bomb Spawner
// ====================================================================================
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb")
	FBombSpawnerProperty BombSpawnerProperty;
	
public:
	void Spawn(const EBombType Type);

	void Shoot(const EBombType Type);

	void Clear() const;

	void SetBombEnergy(const int32 InBombEnergy);

private:
	FVector GetBombSpawnLoc() const;
	
};
