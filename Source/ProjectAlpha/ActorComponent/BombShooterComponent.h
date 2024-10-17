// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BombShooterComponent.generated.h"

class AStageGameMode;
class ABombActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UBombShooterComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<AStageGameMode> GameMode;
	
public:
	UBombShooterComponent();

public:
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb")
	TSubclassOf<ABombActor> BombActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float FireSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float MaxSpeed = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Bomb")
	bool bFireAutomatic = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float AutomaticFireInitDelay = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bomb")
	float AutomaticFirePeriod = 1.f;

private:
	UPROPERTY()
	float AutomaticFireTick = 0.f;

	UPROPERTY()
	float AutomaticFireInitTick = 0.f;
	
public:
	UFUNCTION(BlueprintCallable, Category="Bomb")
	void Fire();
	
};
