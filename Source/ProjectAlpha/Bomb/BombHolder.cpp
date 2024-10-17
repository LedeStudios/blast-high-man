// Copyright Lede Studios. All Rights Reserved.


#include "BombHolder.h"

#include "BombBase.h"

void UBombHolder::AddLast(IBomb* InBomb)
{
	Bombs.Add(InBomb);
}

void UBombHolder::Explode()
{
	if (!Bombs.IsEmpty())
	{
		if (IBomb* Bomb = Bombs[0])
		{
			Bomb->Explode(Bomb->GetExplodeLocation());
		}
		Bombs.RemoveAt(0);
	}
}

void UBombHolder::Clear()
{
	for (IBomb* Bomb : Bombs)
	{
		Bomb->Remove();
	}
	Bombs.Empty();
}
