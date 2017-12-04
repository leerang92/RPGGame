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
			SetupGrid(Slot);
			UUIInventorySlot* ItemSlot = Cast<UUIInventorySlot>(Slot);
			check(ItemSlot);
			SlotArr.Add(ItemSlot);
		}
	}
}

void UUIInventory::AddItem(FItemInfo NewItem)
{
	// �̹� �������� �ִ��� Ȯ���� ���� �� �� ���Կ� ������ ����
	if (!IsPresentItem(NewItem))
	{
		for (auto &Slot : SlotArr)
		{
			if (Slot->IsEmpty())
			{
				Slot->SetupSlot(NewItem);
				break;
			}
		}
	}
}

bool UUIInventory::IsPresentItem(FItemInfo & NewItem)
{
	for (auto &Slot : SlotArr)
	{
		if (Slot->GetItemInfo().Name == NewItem.Name)
		{
			Slot->SetupSlot(NewItem);
			return true;
		}
	}
	return false;
}


