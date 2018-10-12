// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"




void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnGrass();
}

void UGrassComponent::SpawnGrass()
{
	for (size_t i = 0; i < SpawnAmount; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBoxExtend);
		float RandRotat = FMath::RandRange(-180.f, 180.f);
		FRotator SpawnRotation = FRotator(0, RandRotat, 0);

		float RandScale = FMath::RandRange(1.f, SpawnMaxScale);
		FVector SpawnScale = FVector(RandScale);

		FTransform SpawnTransform(SpawnRotation, SpawnLocation, SpawnScale);
		AddInstance(SpawnTransform);
	}
}
