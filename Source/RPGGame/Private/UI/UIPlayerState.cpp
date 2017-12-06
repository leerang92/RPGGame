// Fill out your copyright notice in the Description page of Project Settings.

#include "UIPlayerState.h"
#include "RPGGameCharacter.h"

void UUIPlayerState::NativeConstruct()
{
	Super::NativeConstruct();

	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(GetOwningPlayerPawn());
	if (PC)
	{
		MaxHP = PC->GetMaxHP();
	}
}

void UUIPlayerState::SetHP(float NewHP)
{
	const float HpPersent = ((NewHP / MaxHP) * 100.0f) / 100.0f;
	HPBar->SetPercent(HpPersent);
}

void UUIPlayerState::SetMana(float NewMana)
{
	ManaBar->SetPercent((NewMana / MaxMana) * 100.0f);
}
