// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonsterController.h"
#include "BaseMonster.h"

ABaseMonsterController::ABaseMonsterController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board Component"));

	TargetPawnKeyName = TEXT("TargetPawn");
	AIStateKeyName = TEXT("State");
}

void ABaseMonsterController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	ABaseMonster* Monster = Cast<ABaseMonster>(InPawn);
	check(Monster);
	if (Monster->BehaviorTree->BlackboardAsset)
	{
		BlackboardComp->InitializeBlackboard(*Monster->BehaviorTree->BlackboardAsset);
	}
	BehaviorComp->StartTree(*Monster->BehaviorTree);
}

void ABaseMonsterController::UnPossess()
{
	Super::UnPossess();

	BehaviorComp->StopTree();
}

void ABaseMonsterController::SetTargetPawn(APawn * NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetPawnKeyName, NewTarget);
	}
}

void ABaseMonsterController::SetAIState(EAIState State)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(AIStateKeyName, State);
	}
}
