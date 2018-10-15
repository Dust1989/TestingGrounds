// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "AI/Navigation/NavModifierVolume.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UActorPool::AddNavMesh(class AActor* VolumeToAdd)
{
	FoundNavMesh.Push(VolumeToAdd);
}

void UActorPool::AddNavModify(class AActor* ModifyToAdd)
{
	NavModifierVolume.Push(ModifyToAdd);
}

AActor* UActorPool::CheckoutNavMesh()
{
	if (FoundNavMesh.Num() == 0) { return nullptr; }
	return FoundNavMesh.Pop();
}

AActor* UActorPool::CheckoutNavModify()
{
	if (NavModifierVolume.Num() == 0) { return nullptr; }
	return NavModifierVolume.Pop();
}

void UActorPool::ReturnNavMesh(AActor* ActorToReturn)
{
	FoundNavMesh.Push(ActorToReturn);
}

void UActorPool::ReturnNavModifier(AActor* ActorToReturn)
{
	NavModifierVolume.Push(ActorToReturn);
}

