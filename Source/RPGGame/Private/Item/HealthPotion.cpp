// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPotion.h"
#include "RPGCharacter.h"


void AHealthPotion::OnUsed(APawn * Owner)
{
	Super::OnUsed(Owner);

	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);

	PC->SetHP(HP);
}

