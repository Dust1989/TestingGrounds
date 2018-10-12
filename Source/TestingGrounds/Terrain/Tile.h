// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void PlaceActor(TSubclassOf<AActor> Class, int32 MinNum, int32 MaxNum = 1, float Radius = 100, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Clean")
	void CleanActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SpawnActor(TSubclassOf<AActor> Class, FVector Location, float Scale);

	bool CanSpawnLocation(FVector Location, float Radius);

	bool FindSpawnPoint(FVector& Location, float Radius);

	TArray<AActor*> SpawnActors;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
