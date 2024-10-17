// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PA_Controller.generated.h"

class USettingsSubsystem;
class APaperActor;
class AStageGameMode;
class APA_Character;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTALPHA_API APA_Controller : public APlayerController
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<APA_Character> PlayerCharacter;
	TWeakObjectPtr<AStageGameMode> GameMode;
	TWeakObjectPtr<USettingsSubsystem> Settings;

public:
	APA_Controller();
	
public:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Widget")
	TSubclassOf<UUserWidget> EscWidget;

	UPROPERTY()
	TObjectPtr<UUserWidget> Widget;

public:
	UFUNCTION(BlueprintCallable, Category="EscMenu")
	void OpenEscMenu();

	UFUNCTION(BlueprintCallable, Category="EscMenu")
	void CloseEscMenu();

	UFUNCTION(BlueprintCallable, Category="EscMenu")
	bool IsEscMenuOpened() const;
	
protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RepulsionBombAction;

	/** Active Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttractionBombAction;

	/** Regen Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RegenAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

	/** Esc Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EscAction;
	
protected:
	void Jump();

	void StopJumping();
	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void ChargeAttractionBomb();

	void ShootAttractionBomb();

	void ChargeRepulsionBomb();

	void ShootRepulsionBomb();

	void Regen();

	void Interaction();

	void Esc();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(UIMin=0.f, UIMax=180.f))
	float MaxPitchAngle = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(UIMin=-180.f, UIMax=0.f))
	float MinPitchAngle = -45.f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ladder")
	bool bUseLadder = false;
	
	
};

