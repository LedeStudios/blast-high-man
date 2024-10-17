// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Data/FontTableRow.h"
#include "LocalizedTextBlock.generated.h"

UENUM(BlueprintType)
enum class ETextType : uint8
{
	Title,
	Description,
	Paper
};

UCLASS(BlueprintType)
class PROJECTALPHA_API ULocalizedTextBlock : public UTextBlock
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Localization")
	FFontTableRow FontTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Localization")
	ETextType Type = ETextType::Title;

public:
	virtual void OnWidgetRebuilt() override;

	virtual void SynchronizeProperties() override;

private:
	void UpdateFont(const FFontTableContent& Content);
	
};
