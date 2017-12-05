// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInst.h"

void UCharacterAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PC = Cast<ARPGGameCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInst::AnimNotify_NextAttack(UAnimNotify* Notify)
{
	if (PC && PC->bInputAttack)
	{
		PC->ComboAttack();
	}
}

void UCharacterAnimInst::AnimNotify_StopAttack(UAnimNotify* Notify)
{
	if (PC)
	{
		PC->StopAttackAnim();
	}
}




