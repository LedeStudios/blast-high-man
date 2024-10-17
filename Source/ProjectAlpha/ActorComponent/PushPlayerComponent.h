// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "PushPlayerComponent.generated.h"


class APA_Character;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTALPHA_API UPushPlayerComponent : public UArrowComponent
{
	GENERATED_BODY()

public:
	UPushPlayerComponent();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Push")
	float PushPower = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Push")
	bool bIsAutomatic = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Push")
	float AutomaticPushPeriod = 1.f;

private:
	UPROPERTY()
	float AutomaticPushTick = 0.f;
	
public:
	void SetAutomatic(const bool InAutomatic) { bIsAutomatic = InAutomatic; }

	bool IsAutomatic() const { return bIsAutomatic; }
	
public:
	void Push(const ACharacter* Character) const;

protected:
	UPROPERTY()
	TWeakObjectPtr<APA_Character> Player;
	
protected:
	UFUNCTION(BlueprintCallable, Category="Push")
	void OnBeginOverlap(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="Push")
	void OnEndOverlap(AActor* InActor);
	
};
