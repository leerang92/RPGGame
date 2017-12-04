// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPotion.h"
#include "RPGGameCharacter.h"


void AHealthPotion::OnUsed(APawn * Owner)
{
	Super::OnUsed(Owner);

	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);

	PC->SetHP(HP);
}

