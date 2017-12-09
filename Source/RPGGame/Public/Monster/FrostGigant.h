// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BaseMonster.h"
#include "FrostGigant.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AFrostGigant : public ABaseMonster
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void SetAttack();

	virtual void ComboAttack() override;
};
