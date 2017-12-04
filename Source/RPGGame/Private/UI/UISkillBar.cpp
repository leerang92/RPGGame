// Fill out your copyright notice in the Description page of Project Settings.

#include "UISkillBar.h"


void UUISkillBar::NativeConstruct()
{
	Super::NativeConstruct();

	CreateSlot();
}

void UUISkillBar::CreateSlot()
{
	if (SlotClass == nullptr)
	{
		return;
	}

	for (int i = 0; i < ColumnSize; ++i)
	{
		UUserWidget* Slot = CreateWidget<UUserWidget>(GetWorld(), SlotClass);
		if (Slot)
		{
			SetupGrid(Slot);
			USkillSlot* SkillSlot = Cast<USkillSlot>(Slot);
			check(SkillSlot);
			SlotArr.Add(SkillSlot);
			// Slot Drop여부 설정
			SkillSlot->SetDrop(true);
		}
	}
}

void UUISkillBar::OnUsedSkill(int Index)
{
	if (SlotArr.Num() > Index && SlotArr[Index]->IsUseSkill())
	{
		SlotArr[Index]->OnUsed();
	}
}

