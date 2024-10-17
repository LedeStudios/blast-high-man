// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "BombComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BombBase.generated.h"


class UProjectileMovementComponent;

USTRUCT(Blueprintable)
struct FBombProperty
{
	GENERATED_BODY()

public:
	FBombProperty():
	Radius(1.0f),
	Power(1.0f)
	{}

	FBombProperty(const float InRange, const float InPower):
	Radius(InRange),
	Power(InPower)
	{}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power;
	
};

UCLASS()
class PROJECTALPHA_API ABombBase : public AActor, public IBomb
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bomb")
	USphereComponent* BombCollision;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	FBombProperty Property;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	FVector LaunchVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	EBombType BombType = EBombType::Repulsion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bomb")
	int32 ChargeLevel = 0;

public:
	ABombBase();

	virtual void BeginPlay() override;

public:
	void SetLaunchVelocity(const FVector& InVelocity) const;
	
public:
	virtual void SetBombType(const EBombType Type) override;
	
	UFUNCTION(BlueprintCallable, Category="Bomb")
	virtual void Explode(const FVector& Pos) override;

	virtual FVector GetExplodeLocation() override;

	virtual int32 GetChargeLevel() override;

	virtual void SetChargeLevel(const int32 Level) override;
	
	virtual void Remove() override;

	UFUNCTION()
	void OnPlatformHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category="Bomb")
	UProjectileMovementComponent* GetProjectileMovementComponent() { return ProjectileMovementComponent; }

	USphereComponent* GetBombCollision() const { return BombCollision; }
};
