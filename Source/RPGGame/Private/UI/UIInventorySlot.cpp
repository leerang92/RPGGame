// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventorySlot.h"
#include "BaseItem.h"

void UUIInventorySlot::SetupSlot(FItemInfo Info)
{
	if (IsEmpty()) // 슬롯이 비었을 때
	{
		ItemInfo = Info;
		SetSlotStyle(*SlotImage, ItemInfo.Image);
		SetAmountText(ItemInfo.Amount);
	}
	else // 이미 슬롯에 아이템이 있을 때
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
			// 사용한 아이템 수량 감소 및 0 이하일 때 삭제
			--ItemInfo.Amount;
			if (ItemInfo.Amount <= 0)
			{
				ItemInfo = {};
				SetSlotStyle(*SlotImage, nullptr);
			}

			// 아이템 사용
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
