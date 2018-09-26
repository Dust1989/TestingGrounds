// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_AIPatrol.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "AIController.h"
#include "AIPatrolRouteComponent.h"

EBTNodeResult::Type UBTT_AIPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Next Index is: %i"), Index);

	auto AICharactor = Cast<ATP_ThirdPersonCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!ensure(AICharactor)) { return EBTNodeResult::Aborted; }

	auto PatrolRouteComponent = AICharactor->FindComponentByClass<UAIPatrolRouteComponent>();

	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Aborted; }
	TArray<AActor*> PatrolPoints = PatrolRouteComponent->GetPatrolPoints();

	AActor* PatrolPoint = nullptr;

	if (PatrolPoints.IsValidIndex(0))
	{
		PatrolPoint = PatrolPoints[Index];
	}

	if (PatrolPoint != nullptr)
	{
		BlackBoardComp->SetValueAsObject(TargetPatrolPoint.SelectedKeyName, PatrolPoint);

		int32 NextIndex = (Index + 1) % PatrolPoints.Num();
		BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	}
	

	return EBTNodeResult::Succeeded;
}

