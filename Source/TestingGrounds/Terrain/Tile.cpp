// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavMeshOffset = FVector(2010.f, 0.f, 200.f);

	NavModifierOffset = FVector(3995.f, 0.f, 0.f);
}

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> Class, int32 MinNum, int32 MaxNum, float Radius, float MinScale, float MaxScale)
{
	int32 NumToSpawn = FMath::RandRange(MinNum, MaxNum);
	for (size_t i = 0; i < NumToSpawn; i++)
	{
		FSpawnInfo SpawnInfo;

		SpawnInfo.Scale = FMath::RandRange(MinScale, MaxScale);
		SpawnInfo.Rotation = FMath::RandRange(-180.f, 180.f);
		if (FindSpawnPoint(SpawnInfo.Location, Radius * SpawnInfo.Scale))
		{
			SpawnActor(Class, SpawnInfo);
		}
	}
}


void ATile::PlaceActor(TSubclassOf<AActor> Class, int32 MinNum, int32 MaxNum, float Radius, float MinScale, float MaxScale)
{	
	RandomlyPlaceActors(Class, MinNum, MaxNum, Radius, MinScale, MaxScale);
}

void ATile::PlaceAI(TSubclassOf<APawn> Class, int32 MinNum, int32 MaxNum, float Radius)
{
	RandomlyPlaceActors(Class, MinNum, MaxNum, Radius, 1, 1);
}

void ATile::CleanActors()
{
	for (auto actor : SpawnActors)
	{
		actor->Destroy();
	}
	for (APawn* AI : SpawnAIs)
	{
		AI->Destroy();
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	
}

void ATile::SpawnActor(TSubclassOf<AActor> Class, const FSpawnInfo& SpawnInfo)
{
	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(Class);

	SpawnActor->SetActorRelativeLocation(SpawnInfo.Location);
	SpawnActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	SpawnActor->SetActorScale3D(FVector(SpawnInfo.Scale));

	SpawnActor->SetActorRotation(FRotator(0, SpawnInfo.Rotation, 0));

	SpawnActors.Push(SpawnActor);
}

void ATile::SpawnActor(TSubclassOf<APawn> Class, const FSpawnInfo& SpawnInfo)
{
	APawn* SpawnAI = GetWorld()->SpawnActor<APawn>(Class);
	SpawnAI->SpawnDefaultController();
	SpawnAI->Tags.Add(FName("Enemy"));

	SpawnAI->SetActorRelativeLocation(SpawnInfo.Location);
	SpawnAI->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

/*	DrawDebugSphere(GetWorld(), Info.Location, 100, 32, FColor::Green, true);*/

	SpawnAI->SetActorRotation(FRotator(0, SpawnInfo.Rotation, 0));

	SpawnAIs.Push(SpawnAI);
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

void ATile::UpdateNavMeshVolumePosition()
{
	NavMeshBoundsVolume = NavMeshPool->CheckoutNavMesh();

	NavModifierVolume = NavMeshPool->CheckoutNavModify();

	if (NavMeshBoundsVolume != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s checkOut %s"), *this->GetName(), *NavMeshBoundsVolume->GetName());

		NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavMeshOffset);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not enough actor in pool"), *this->GetName());
	}

	if (NavModifierVolume != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s checkOut %s"), *this->GetName(), *NavModifierVolume->GetName());

		NavModifierVolume->SetActorLocation(GetActorLocation() + NavModifierOffset);		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Not enough actor in pool"), *this->GetName());
	}
	
	GetWorld()->GetNavigationSystem()->Build();
}


// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetNavMeshPool(class UActorPool* PoolToSet)
{
	NavMeshPool = PoolToSet;

	UpdateNavMeshVolumePosition();
}

void ATile::ReturnNavMesh()
{
	UE_LOG(LogTemp, Warning, TEXT("Return...."));

	if (NavMeshBoundsVolume != nullptr && NavMeshPool != nullptr)
	{
		NavMeshPool->ReturnNavMesh(NavMeshBoundsVolume);
		UE_LOG(LogTemp, Warning, TEXT("Return %s"), *NavMeshBoundsVolume->GetName());
	}

	if (NavModifierVolume != nullptr && NavMeshPool != nullptr)
	{
		NavMeshPool->ReturnNavModifier(NavModifierVolume);
		UE_LOG(LogTemp, Warning, TEXT("Return %s"), *NavModifierVolume->GetName());
	}
}

