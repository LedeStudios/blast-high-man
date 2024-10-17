// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "BombHolder.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTALPHA_API UBombHolder : public UObject
{
	GENERATED_BODY()

protected:
	TArray<IBomb*> Bombs;

public:
	void AddLast(IBomb* InBomb);

	void Explode();

	void Clear();
	
};
