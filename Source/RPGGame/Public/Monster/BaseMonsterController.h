// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BaseMonsterController.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API ABaseMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABaseMonsterController();

	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	void SetTargetPawn(APawn* NewTarget);

	void SetAIState(EAIState State);

	UPROPERTY(EditAnywhere, Category = Behavior)
	UBehaviorTreeComponent* BehaviorComp;
	
	UPROPERTY(EditAnywhere, Category = Behavior)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = AI)
	FName TargetPawnKeyName;

	UPROPERTY(EditAnywhere, Category = AI)
	FName AIStateKeyName;
	
};
