// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PA_BombGaugeArea.generated.h"

class APA_Character;

UCLASS()
class PROJECTALPHA_API APA_BombGaugeArea : public AActor
{
	GENERATED_BODY()

public:
	APA_BombGaugeArea();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	int GaugeRegenAmount;

public:
	UFUNCTION(BlueprintCallable, Category="Bomb")
	void RegenBombGauge(APA_Character* Character) const;

};
