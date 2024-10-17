// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "BackgroundButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UBackgroundButton : public UButton
{
	GENERATED_BODY()

public:
	UBackgroundButton();

protected:
	virtual void OnWidgetRebuilt() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	FColor HoveredBackgroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	float HoveredBackgroundAlpha = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	float UnhoveredBackgroundAlpha = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	TObjectPtr<USoundWave> HoverSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Background")
	TObjectPtr<USoundWave> ClickSound;

protected:
	UPROPERTY(VisibleAnywhere, Category="Background")
	bool bIsSelected;
	
public:
	UFUNCTION(BlueprintCallable, Category="Background")
	void Select(bool InSelected);

	UFUNCTION(BlueprintCallable, Category="Background")
	bool IsSelected();
	
private:
	UFUNCTION()
	void Click();

	UFUNCTION()
	void Hover();

	UFUNCTION()
	void Unhover();

private:
	void UpdateBackgroundAlphaToHovered();

	void UpdateBackgroundAlphaToUnhovered();
	
};

