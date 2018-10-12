// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActor(TSubclassOf<AActor> Class, int32 MinNum, int32 MaxNum, float Radius, float MinScale, float MaxScale)
{	
	int32 NumToSpawn = FMath::RandRange(MinNum, MaxNum);
	for (size_t i = 0; i < NumToSpawn; i++)
	{
		FVector SpawnLocation;
		float SpawnScale = FMath::RandRange(MinScale, MaxScale);
		if (FindSpawnPoint(SpawnLocation, Radius * SpawnScale))
		{
			SpawnActor(Class, SpawnLocation, SpawnScale);
		}		
	}	
}

void ATile::CleanActors()
{
	for (auto actor : SpawnActors)
	{
		actor->Destroy();
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATile::SpawnActor(TSubclassOf<AActor> Class, FVector Location, float Scale)
{
	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(Class);

	SpawnActor->SetActorRelativeLocation(Location);
	SpawnActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	SpawnActor->SetActorScale3D(FVector(Scale));

	float SpawnRotation = FMath::RandRange(-180.f, 180.f);
	SpawnActor->SetActorRotation(FRotator(0, SpawnRotation, 0));

	SpawnActors.Add(SpawnActor);
}

bool ATile::CanSpawnLocation(FVector Location, float Radius)
{
	FHitResult Hit;
	FVector WorldLocation = ActorToWorld().TransformPosition(Location);
	bool HitResult = GetWorld()->SweepSingleByChannel(
		Hit, 
		WorldLocation,
		WorldLocation,
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));

	//TODO Delete the debug line
	/*
	FColor HitColor = HitResult ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), WorldLocation, 0, Radius, FQuat::Identity, HitColor, true);
	*/
	
	return !HitResult;
}

bool ATile::FindSpawnPoint(FVector& Location, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	
	int MAX_ATTEMPTS = 1000;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		Location = FMath::RandPointInBox(Bounds);
		if (CanSpawnLocation(Location, Radius))
		{
			return true;
		}
	}
	return false;
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

