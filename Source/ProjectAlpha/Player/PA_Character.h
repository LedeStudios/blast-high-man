// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PaperActor.h"
#include "GameFramework/Character.h"
#include "PA_Character.generated.h"

class ACheckpointActor;
class UFootstepComponent;
class UCheckpoint;
class UBombComponent;
enum class EBombType : uint8;
class APA_BombGaugeArea;
class UBombHolder;
class ABombBase;
class IBomb;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJump_Delegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLand_Delegate, const FHitResult&, Hit);

UCLASS()
class PROJECTALPHA_API APA_Character : public ACharacter
{
	GENERATED_BODY()

// ====================================================================================
//  Constructor
// ====================================================================================
public:
	APA_Character();

// ====================================================================================
//  Unreal Engine Overrides
// ====================================================================================
protected:
	virtual void BeginPlay() override;

// ====================================================================================
//  First Person Camera
// ====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;
	
public:
	UCameraComponent* GetFPCamera() const { return FirstPersonCamera; }

// ====================================================================================
//  Footstep
// ====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Footstep")
	TObjectPtr<UFootstepComponent> FootstepComponent;

public:
	UFootstepComponent* GetFootstepComponent() { return FootstepComponent; }

// ====================================================================================
//  Bomb Charger
// ====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bomb Charger")
	UBombComponent* BombComponent;

public:
	UBombComponent* GetBombComponent() const { return BombComponent; }

// ====================================================================================
//  Bombs
// ====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bomb")
	TObjectPtr<APA_BombGaugeArea> BombGaugeRegenArea;

public:
	UFUNCTION(BlueprintCallable, Category="Bomb")
	APA_BombGaugeArea* GetBombGaugeRegenArea() const { return BombGaugeRegenArea.Get(); }

	UFUNCTION(BlueprintCallable, Category="Bomb")
	void SetBombGaugeRegenArea(APA_BombGaugeArea* InArea) { BombGaugeRegenArea = InArea; }

// ====================================================================================
//  Checkpoints
// ====================================================================================
protected:
	UPROPERTY(BlueprintReadOnly, Category="Checkpoint")
	TWeakObjectPtr<UCheckpoint> CurrentCheckpoint;

	UPROPERTY(BlueprintReadOnly, Category="Checkpoint")
	TWeakObjectPtr<UCheckpoint> LastCheckpoint;

	UPROPERTY(BlueprintReadOnly, Category="Checkpoint")
	TWeakObjectPtr<ACheckpointActor> LastCheckpointActor;
	
public:
	void SetCheckpoint(UCheckpoint* Checkpoint);

	UCheckpoint* GetCheckpoint() const { return CurrentCheckpoint.Get(); }

	void SetLastCheckpoint(UCheckpoint* Checkpoint);

	UCheckpoint* GetLastCheckpoint() const { return LastCheckpoint.Get(); }

	void SetLastCheckpointActor(ACheckpointActor* InActor);

	ACheckpointActor* GetLastCheckpointActor() const { return LastCheckpointActor.Get(); }

// ====================================================================================
//  Jump & Land Callbacks
// ====================================================================================
public:
	FOnJump_Delegate OnJump;
	FOnLand_Delegate OnLand;

private:
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;

// ====================================================================================
//  Paper
// ====================================================================================
protected:
	UPROPERTY()
	TWeakObjectPtr<APaperActor> PaperActor;

public:
	UFUNCTION(BlueprintCallable, Category="Paper")
	void SetPaperActor(APaperActor* InActor)
	{
		PaperActor = InActor;
	}

	UFUNCTION(BlueprintCallable, Category="Paper")
	APaperActor* GetPaperActor() const
	{
		return PaperActor.Get();
	}

// ====================================================================================
//  Trigger
// ====================================================================================
protected:
	UPROPERTY()
	TWeakObjectPtr<AActor> ActorTriggerActor;

public:
	UFUNCTION(BlueprintCallable, Category="Trigger")
	void SetActorTriggerActor(AActor* InActor) { ActorTriggerActor = InActor; }

	UFUNCTION(BlueprintCallable, Category="Trigger")
	AActor* GetActorTriggerActor() const { return ActorTriggerActor.Get(); }
	
};
