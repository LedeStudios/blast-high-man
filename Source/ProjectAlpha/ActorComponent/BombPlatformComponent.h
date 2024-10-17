// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/ArrowComponent.h"
#include "BombPlatformComponent.generated.h"

class AStageGameMode;

UENUM()
enum class EBombPlatformType
{
	Impact,
	Destruct
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UBombPlatformComponent : public UArrowComponent
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<AStageGameMode> GameMode;
	
public:
	UBombPlatformComponent();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	TObjectPtr<UNiagaraSystem> HitVfx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float ImpactRadius = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float ImpactPower = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float ImpactAdjustmentFactor = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	EBombPlatformType Type = EBombPlatformType::Impact;
	
public:
	void OnHit(const FVector& HitLocation) const;

private:
	void Impact(const FVector& HitLocation) const;

	void Destruct(const FVector& HitLocation) const;
	
};
