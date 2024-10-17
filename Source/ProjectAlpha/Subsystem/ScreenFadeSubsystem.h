// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScreenFadeSubsystem.generated.h"

class UUMGSequencePlayer;
class UWidgetAnimation;
class UFadeWidget;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UScreenFadeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Fade")
	TSubclassOf<UFadeWidget> WidgetClass;

	UPROPERTY(EditAnywhere, Category="Fade")
	TObjectPtr<UWidgetAnimation> FadeInAnim;

	UPROPERTY(EditAnywhere, Category="Fade")
	TObjectPtr<UWidgetAnimation> FadeOutAnim;
	
	UPROPERTY()
	TObjectPtr<UFadeWidget> Widget;

public:
	UFUNCTION(BlueprintCallable, Category="Screen|Fade")
	void FadeIn();

	UFUNCTION(BlueprintCallable, Category="Screen|Fade")
	void FadeOut();

private:
	void Fade(bool bIsFadeOut);
	
};
