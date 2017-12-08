// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventorySlot.h"
#include "BaseItem.h"

void UUIInventorySlot::SetupSlot(FItemInfo Info)
{
	if (IsEmpty()) // ������ ����� ��
	{
		ItemInfo = Info;
		SetSlotStyle(*SlotImage, ItemInfo.Image);
		SetAmountText(ItemInfo.Amount);
	}
	else // �̹� ���Կ� �������� ���� ��
	{
		ItemInfo.Amount += Info.Amount;
		SetAmountText(ItemInfo.Amount);
	}
	
}

void UUIInventorySlot::OnUsed()
{
	if (!IsEmpty() && ItemInfo.ItemClass != nullptr)
	{
		ABaseItem* UsableItem = Cast<ABaseItem>(ItemInfo.ItemClass->GetDefaultObject());
		if (UsableItem)
		{
			// ����� ������ ���� ���� �� 0 ������ �� ����
			--ItemInfo.Amount;
			if (ItemInfo.Amount <= 0)
			{
				ItemInfo = {};
				SetSlotStyle(*SlotImage, nullptr);
			}

			// ������ ���
			UsableItem->OnUsed(GetOwningPlayerPawn());
			SetAmountText(ItemInfo.Amount);
		}
	}
}

void UUIInventorySlot::SetAmountText(int Amount)
{
	//ItemInfo.Amount += Amount;
	if (Amount > 0)
	{
		AmountText->SetText(FText::AsNumber(Amount));
	}
	else
	{
		AmountText->SetText(FText::GetEmpty());
	}
}
