// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterAnimInst.h"

void UCharacterAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PC = Cast<ARPGCharacter>(TryGetPawnOwner());
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
		PC->bIsAttacking = false;
	}
}

void UCharacterAnimInst::AnimNotify_CamShake(UAnimNotify* Notify)
{
	if (PC)
	{
		PC->StartCameraShake();
	}
}

void UCharacterAnimInst::AnimNotify_SlowMotion(UAnimNotify* Notify)
{
	if (PC)
	{
		PC->StartSlowMotion();
	}
}

void UCharacterAnimInst::AnimNotify_MakeNoise(UAnimNotify * Notify)
{
	if (PC)
	{
		PC->MakeNoise(1.0f, PC, PC->GetActorLocation(), 0.5f);
	}
}




