// Fill out your copyright notice in the Description page of Project Settings.

#include "UIBuffBar.h"

void UUIBuffBar::SetBuffIcon(FBuffInfo Info)
{
	if (!IsPresentBuff(Info))
	{
		UUserWidget* Slot = CreateWidget<UUserWidget>(GetWorld(), SlotClass);
		if (Slot && GridPanel)
		{
			UBuffSlot* BuffSlot = Cast<UBuffSlot>(Slot);
			check(BuffSlot);
			BuffSlot->SetSlot(Info, this);
			SlotArr.Add(BuffSlot);
			SetupGrid(Slot);
		}
	}
}

bool UUIBuffBar::IsPresentBuff(FBuffInfo & Info)
{
	for (auto &Slot : SlotArr)
	{
		if (Slot->GetBuffInfo().Name == Info.Name)
		{
			Slot->SetDuration(Info.Duration);
			return true;
		}
	}
	return false;
}

void UUIBuffBar::RemoveSlot(UBuffSlot & RemoveSlot)
{
	for (int i = 0; i < SlotArr.Num(); ++i)
	{
		if (SlotArr[i] == &RemoveSlot)
		{
			RemoveSlot.RemoveFromParent();
			SlotArr.RemoveAt(i);
			RelocationGrid();
			break;
		}
	}
}

void UUIBuffBar::RelocationGrid()
{
	Column = 0;
	Row = 0;

	for (auto Slot : SlotArr)
	{
		SetupGrid(Slot);
	}
}
