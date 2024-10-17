// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WidgetControllerBase.generated.h"

class APA_HUD;

UCLASS()
class PROJECTALPHA_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init(const APA_HUD* HUD) {}
	
};
