// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaperWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UPaperWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Paper")
	TWeakObjectPtr<UTexture2D> PaperTexture;

public:
	void SetPaperTexture(UTexture2D* InTexture);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Paper")
	void OnPaperTextureUpdate(UTexture2D* Texture);
	
};
