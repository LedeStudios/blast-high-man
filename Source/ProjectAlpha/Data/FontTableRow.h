// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FontTableRow.generated.h"

USTRUCT(BlueprintType)
struct FFontTableContent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Content", meta=(AllowedClasses="/Script/Engine.Font"))
	TObjectPtr<UObject> Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Content", meta=(AllowedClasses="/Script/Engine.MaterialInterface"))
	TObjectPtr<UObject> FontMaterial;
	
};

USTRUCT(BlueprintType)
struct FFontTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Font")
	FFontTableContent TitleFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Font")
	FFontTableContent DescriptionFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Font")
	FFontTableContent PaperFont;
	
};
