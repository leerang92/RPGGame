// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillSlot.h"
#include "SlateBrush.h"

void USkillSlot::NativeConstruct()
{
	Super::NativeConstruct();
	bDrop = false;
	bUsed = true;

	SetSlotStyle(*SlotImage, SkillInfo.Image);
}

void USkillSlot::OnUsed()
{

}

void USkillSlot::SetSlot(FSkillInfo Info)
{
	SkillInfo = Info;
	SetSlotStyle(*SlotImage, SkillInfo.Image);
}

void USkillSlot::SetDrop(bool isDrop)
{
	bDrop = isDrop;
}
