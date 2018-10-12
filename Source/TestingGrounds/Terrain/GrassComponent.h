// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Rendering, meta = (BlueprintSpawnableComponent))
class TESTINGGROUNDS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	
	


private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FBox SpawnBoxExtend;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	int32 SpawnAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float SpawnMaxScale = 1.f;

	void SpawnGrass();
};
