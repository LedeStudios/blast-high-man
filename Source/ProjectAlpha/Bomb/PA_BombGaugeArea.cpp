// Copyright Lede Studios. All Rights Reserved.


#include "PA_BombGaugeArea.h"

#include "BombComponent.h"
#include "Player/PA_Character.h"


APA_BombGaugeArea::APA_BombGaugeArea()
{
	PrimaryActorTick.bCanEverTick = false;
	GaugeRegenAmount = 100;
}

void APA_BombGaugeArea::RegenBombGauge(APA_Character* Character) const
{
	UBombComponent* Component = Character->GetBombComponent();
	Component->Clear();
	Component->SetBombEnergy(GaugeRegenAmount);
}


