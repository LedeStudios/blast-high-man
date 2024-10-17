// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombActor.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTALPHA_API ABombActor : public AActor
{
	GENERATED_BODY()

public:
	ABombActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bomb")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bomb")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

public:
	UProjectileMovementComponent* GetProjectileMovementComponent() { return ProjectileMovementComponent; }

protected:
	UFUNCTION(BlueprintCallable, Category="Bomb")
	void OnHit(AActor* Other, const FVector HitLocation);
	
};
