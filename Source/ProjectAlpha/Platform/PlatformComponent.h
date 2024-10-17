// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlatformComponent.generated.h"

class APlatformBase;
class ABombBase;
class IBomb;

UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class EPlatformFlag : uint8
{
	// 기본 지형
	None			 = 0 UMETA(Hidden),

	// 폭탄이 부착되는 지형
	Attachable       = 0x01 << 0 UMETA(DisplayName = "Attachable"),

	// 폭탄이 부착되지 않는 지형 (맞으면 폭탄은 날아가는 힘을 잃고 굴러감)
	NonAttachable    = 0x01 << 1 UMETA(DisplayName = "Non-Attachable"),

	// 폭탄을 튕겨내는 지형 (지형에 따른 폭탄 반사)
	Reflective       = 0x01 << 2 UMETA(DisplayName = "Reflective"),

	// 폭탄이 터지지 않는 지형 (폭탄이 터지지 않고 그 효과만 지속적으로 발생)
	NonExplosive     = 0x01 << 3 UMETA(DisplayName = "Non-Explosive"),

	// 폭탄에 힘을 받는 지형 (인력/척력)
	ForceAffecting   = 0x01 << 4 UMETA(DisplayName = "Force Affecting"),

	// 폭탄에 파괴되는 지형
	Destructible     = 0x01 << 5 UMETA(DisplayName = "Destructible")
};
ENUM_CLASS_FLAGS(EPlatformFlag);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UPlatformComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlatformComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TWeakObjectPtr<APlatformBase> PlatformActor;
	
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="Platform", meta=(Bitmask, BitmaskEnum="EPlatformFlag"))
	uint8 PlatformType;

public:
	int32 GetPlatformTypeBitmask() const;

	bool IsTypeMatch(UPARAM(meta=(Bitmask, BitmaskEnum="EPlatformFlag")) uint8 InFlags) const;

	bool IsTypeMatch(const EPlatformFlag InFlag) const;
	
public:
	virtual void OnBombHit(ABombBase* InBomb, const FHitResult& InHitResult);

	
};
