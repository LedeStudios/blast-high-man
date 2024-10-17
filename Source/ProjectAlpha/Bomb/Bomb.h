// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Bomb.generated.h"

enum class EBombType : uint8;

// This class does not need to be modified.
UINTERFACE()
class UBomb : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTALPHA_API IBomb
{
	GENERATED_BODY()

public:
	virtual void SetBombType(const EBombType Type) = 0;
	
	virtual void Explode(const FVector& Pos) = 0;
	
	virtual FVector GetExplodeLocation() = 0;

	virtual void SetChargeLevel(const int32 Level) = 0;
	
	virtual int32 GetChargeLevel() = 0;
	
	virtual void Remove() = 0;
};
