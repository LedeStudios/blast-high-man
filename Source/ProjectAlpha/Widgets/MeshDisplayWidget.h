// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PA_BaseWidget.h"
#include "MeshDisplayWidget.generated.h"

class UViewport;
/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UMeshDisplayWidget : public UPA_BaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UViewport> Viewport;
	
	TWeakObjectPtr<UStaticMesh> DisplayMesh;

public:
	void SetDisplayMesh(UStaticMesh* InMesh) { DisplayMesh = InMesh; }

	void Show();

	void Hide();
	
};
