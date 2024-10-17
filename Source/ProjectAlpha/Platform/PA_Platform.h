// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PA_Platform.generated.h"

class IBomb;
class UPlatformBehaviorComponent;
struct FHitResult;

UCLASS()
class PROJECTALPHA_API APA_Platform : public AActor
{
	GENERATED_BODY()

public:
	APA_Platform();

protected:
	UFUNCTION(BlueprintCallable, Category="Platform")
	void OnBombHit(TScriptInterface<IBomb> Bomb, const FHitResult& HitResult) { /* Override for handling bomb collisions */ }
	
};
