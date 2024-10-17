// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PA_HUD.generated.h"

class UMeshDisplayWidgetController;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API APA_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UMeshDisplayWidgetController> MeshDisplayWidgetController;

public:
	UMeshDisplayWidgetController* GetMeshDisplayWidgetController() { return MeshDisplayWidgetController; }
	
};
