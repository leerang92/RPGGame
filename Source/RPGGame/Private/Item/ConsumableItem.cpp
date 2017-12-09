// Fill out your copyright notice in the Description page of Project Settings.

#include "ConsumableItem.h"
#include "RPGCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AConsumableItem::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->SetSimulatePhysics(true);
}

void AConsumableItem::OnPickup(APawn * Owner)
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);
	check(PC);

	PC->AddItem(this);

	Super::OnPickup(Owner);
}

void AConsumableItem::OnUsed(APawn * Owner)
{
	Super::OnUsed(Owner);

	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);
	check(PC);

	// 버프 아이콘 생성
	PC->GetMainHUD()->GetBuffBar()->SetBuffIcon(BuffInfo);
}
