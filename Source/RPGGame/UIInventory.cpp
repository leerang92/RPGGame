// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventory.h"

void UUIInventory::NativeConstruct()
{
	Super::NativeConstruct();

	CreateItemList();
}

void UUIInventory::CreateItemList()
{
	if (SlotClass == nullptr)
	{
		return;
	}

	for (int i = 0; i < ListSize; ++i)
	{
		UUserWidget* Slot = CreateWidget<UUserWidget>(GetWorld(), SlotClass);
		if (Slot != nullptr)
		{
			SetupGrid(GridPanel->AddChildToUniformGrid(Slot));
			UBaseItemSlot* ItemSlot = Cast<UBaseItemSlot>(Slot);
			check(ItemSlot);
			SlotArr.Add(ItemSlot);
		}
	}
}

void UUIInventory::SetupGrid(UUniformGridSlot * Slot)
{
	Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	Slot->SetColumn(Column);
	Slot->SetRow(Row);

	++Column;
	if (Column >= ColumnSize)
	{
		Column = 0;
		++Row;
	}
}

void UUIInventory::AddItem(FItemInfo NewItem)
{
	for (int i = 0; i < SlotArr.Num(); ++i)
	{
		if (SlotArr[i]->IsEmpty())
		{
			SlotArr[i]->SetupSlot(NewItem);
			break;
		}
	}
}


