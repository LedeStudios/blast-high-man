// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BombComponent.h"
#include "GameFramework/Actor.h"
#include "BombChargeDisplay.generated.h"

enum class EBombType : uint8;

UCLASS()
class PROJECTALPHA_API ABombChargeDisplay : public AActor
{
	GENERATED_BODY()

public:
	ABombChargeDisplay();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bomb")
	int32 ChargeLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bomb")
	EBombType BombType = EBombType::Attraction;

public:
	void SetChargeLevel(const int32 InLevel) { ChargeLevel = InLevel; }

	int32 GetChargeLevel() const { return ChargeLevel; }

	void SetBombType(const EBombType InType) { BombType = InType; }

	EBombType GetBombType() const { return BombType; }
	
};
