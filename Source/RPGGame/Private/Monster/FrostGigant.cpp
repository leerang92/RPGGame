// Fill out your copyright notice in the Description page of Project Settings.

#include "FrostGigant.h"
#include "RPGCharacter.h"


void AFrostGigant::BeginPlay()
{
	Super::BeginPlay();

	bAttacking = false;
}

void AFrostGigant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIState == EAIState::ATTACK)
	{
		if (!IsAttack() && !bAttacking)
		{
			SetFocus();
		}
		else if(IsAttack())
		{
			UE_LOG(LogClass, Warning, TEXT("Check"));
			ComboAttack();
		}
	}
}

void AFrostGigant::SetAttack()
{
	AIState = EAIState::ATTACK;
	MonsterCon->SetAIState(AIState);

	AttackIndex = 0;
	//ComboAttack();
}

void AFrostGigant::ComboAttack()
{
	if (AttackIndex >= AttackAnims.Num())
	{
		AttackIndex = 0;
	}
	PlayAnimation(AttackAnims[AttackIndex]);
	++AttackIndex;
}

