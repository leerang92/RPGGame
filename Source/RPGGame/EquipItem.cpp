// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipItem.h"
#include "RPGGameCharacter.h"

void AEquipItem::OnPickup(APawn* Owner)
{
	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);
	check(PC);

	//Super::OnPickup(Owner);
	PC->AddItem(this);
}

void AEquipItem::OnUsed(APawn* Owner)
{
	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);
	check(PC);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FName AttachPoint = TEXT("hand_rWeaponSocket");
	MeshComp->AttachToComponent(PC->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
}
