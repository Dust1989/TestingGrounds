// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnInfo
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};


UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActor(TSubclassOf<AActor> Class, int32 MinNum, int32 MaxNum = 1, float Radius = 100, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceAI(TSubclassOf<APawn> Class, int32 MinNum, int32 MaxNum = 1, float Radius = 100);

	UFUNCTION(BlueprintCallable, Category = "Clean")
	void CleanActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> Class, int32 MinNum, int32 MaxNum = 1, float Radius = 100, float MinScale = 1, float MaxScale = 1);

	void SpawnActor(TSubclassOf<AActor> Class, const FSpawnInfo& SpawnInfo);

	void SpawnActor(TSubclassOf<APawn> Class, const FSpawnInfo& SpawnInfo);

	bool CanSpawnLocation(FVector Location, float Radius);

	bool FindSpawnPoint(FVector& Location, float Radius);

	TArray<AActor*> SpawnActors;

	TArray<APawn*> SpawnAIs;

	class UActorPool* NavMeshPool;

	AActor* NavMeshBoundsVolume;

	AActor* NavModifierVolume;

	UPROPERTY(EditDefaultsOnly, Category = "NavMeshVolume")
	FVector NavMeshOffset;

	UPROPERTY(EditDefaultsOnly, Category = "NavMeshVolume")
	FVector NavModifierOffset;

	void UpdateNavMeshVolumePosition();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "NavMeshVolume")
	void SetNavMeshPool(class UActorPool* PoolToSet);
	
	UFUNCTION(BlueprintCallable, Category = "NavMeshVolume")
	void ReturnNavMesh();
};


