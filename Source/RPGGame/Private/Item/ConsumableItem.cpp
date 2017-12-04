// Fill out your copyright notice in the Description page of Project Settings.

#include "ConsumableItem.h"
#include "RPGGameCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AConsumableItem::OnPickup(APawn * Owner)
{
	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);
	check(PC);

	PC->AddItem(this);

	Super::OnPickup(Owner);
}

void AConsumableItem::OnUsed(APawn * Owner)
{
	Super::OnUsed(Owner);

	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);
	check(PC);

	PC->GetMainHUD()->GetBuffBar()->SetBuffIcon(BuffInfo);
}
