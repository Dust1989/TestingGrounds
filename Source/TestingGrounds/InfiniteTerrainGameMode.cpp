// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "AI/Navigation/NavModifierVolume.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshPool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	auto NavModifierVolumeIterator = TActorIterator<ANavModifierVolume>(GetWorld());
	
	while (VolumeIterator) {
		NavMeshPool->AddNavMesh(*VolumeIterator);
		++VolumeIterator;
	}

	while (NavModifierVolumeIterator) {

		NavMeshPool->AddNavModify(*NavModifierVolumeIterator);
		++NavModifierVolumeIterator;
	}
}


