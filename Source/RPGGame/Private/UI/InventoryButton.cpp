// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryButton.h"


void UInventoryButton::OnUsed()
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		PC->GetMainHUD()->ActiveInventory();
	}
}

