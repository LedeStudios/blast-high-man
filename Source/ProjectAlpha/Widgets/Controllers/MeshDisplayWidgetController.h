// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WidgetControllerBase.h"
#include "UObject/Object.h"
#include "MeshDisplayWidgetController.generated.h"

class APA_HUD;
class UMeshDisplayWidget;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UMeshDisplayWidgetController : public UWidgetControllerBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="MeshDisplay")
	TSubclassOf<UMeshDisplayWidget> WidgetClass;
	
public:
	virtual void Init(const APA_HUD* HUD) override;
	
protected:
	UPROPERTY()
	TObjectPtr<UMeshDisplayWidget> Widget;

public:
	UMeshDisplayWidget* GetWidget() { return Widget; }
	
};
