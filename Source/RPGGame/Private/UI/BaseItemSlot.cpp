// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseItemSlot.h"
#include "BaseItem.h"

void UBaseItemSlot::SetupSlot(FItemInfo Info)
{
	if (Info.Image != nullptr && IsEmpty())
	{
		ItemInfo = Info;
		SetSlotStyle(Info.Image);
	}
	SetAmountText(ItemInfo.Amount);
}

void UBaseItemSlot::SetSlotStyle(UTexture2D * Image)
{
	FSlateBrush Brush;
	if (Image != nullptr)
	{
		Brush.SetResourceObject(Image);
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

	ItemImage->SetBrush(Brush);
}

void UBaseItemSlot::SetAmountText(int Amount)
{
	ItemInfo.Amount += Amount;
	if (Amount > 0)
	{
		AmountText->SetText(FText::AsNumber(Amount));
	}
	else
	{
		AmountText->SetText(FText::GetEmpty());
	}
}

bool UBaseItemSlot::IsEmpty() const
{
	return ItemInfo.Image == nullptr;
}

void UBaseItemSlot::UseSlotItem()
{
	if (!IsEmpty() && ItemInfo.ItemClass != nullptr)
	{
		ABaseItem* UsableItem = Cast<ABaseItem>(ItemInfo.ItemClass->GetDefaultObject());
		if (UsableItem)
		{
			UsableItem->OnUsed(GetOwningPlayerPawn());

			--ItemInfo.Amount;
			if (ItemInfo.Amount <= 0)
			{
				ItemInfo = {};
				SetSlotStyle(nullptr);
			}
			SetupSlot(ItemInfo);
		}
	}
}
