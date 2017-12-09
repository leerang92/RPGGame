// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonsterAnimInst.h"

void UBaseMonsterAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Monster = Cast<ABaseMonster>(TryGetPawnOwner());
}

void UBaseMonsterAnimInst::AnimNotify_NextAttack(UAnimNotify * Notify)
{
	if (Monster)
	{
		Monster->ComboAttack();
	}
}

void UBaseMonsterAnimInst::AnimNotify_StartAttack(UAnimNotify * Notify)
{
	if (Monster)
	{
		Monster->bAttacking = true;
	}
}

void UBaseMonsterAnimInst::AnimNotify_EndAttack(UAnimNotify * Notify)
{
	if (Monster)
	{
		Monster->bAttacking = false;
	}
}

void UBaseMonsterAnimInst::AnimNotify_StopAttack(UAnimNotify * Notify)
{
	if (Monster)
	{
		Monster->bAttacking = false;
	}
}
