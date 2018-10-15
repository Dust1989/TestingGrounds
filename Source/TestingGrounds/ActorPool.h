// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPool();

protected:


public:	

	void AddNavMesh(class AActor* VolumeToAdd);

	void AddNavModify(class AActor* ModifyToAdd);
	
	AActor* CheckoutNavMesh();

	AActor* CheckoutNavModify();

	void ReturnNavMesh(AActor* ActorToReturn);

	void ReturnNavModifier(AActor* ActorToReturn);

private:
	TArray < class AActor* >  FoundNavMesh;

	TArray < class AActor* >  NavModifierVolume;
	
};
