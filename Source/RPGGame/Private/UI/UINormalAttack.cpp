// Fill out your copyright notice in the Description page of Project Settings.

#include "UINormalAttack.h"


void UUINormalAttack::OnUsed()
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		PC->StartAttack();
	}
}

void UUINormalAttack::EndUsed()
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		PC->StopAttack();
	}
}

