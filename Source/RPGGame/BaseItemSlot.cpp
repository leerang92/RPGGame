// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseItemSlot.h"

void UBaseItemSlot::SetupSlot(FItemInfo Info)
{
	
	if (Info.Image != nullptr && IsEmpty())
	{
		ItemInfo = Info;
		SetSlotStyle(Info.Image);
	}
	else
	{
		ItemInfo.Amount += Info.Amount;
		SetAmountText(ItemInfo.Amount);
	}
}

void UBaseItemSlot::SetSlotStyle(UTexture2D * Image)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Image);
	Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	ItemImage->SetBrush(Brush);
}

void UBaseItemSlot::SetAmountText(int Amount)
{
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