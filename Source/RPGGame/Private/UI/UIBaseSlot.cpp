// Fill out your copyright notice in the Description page of Project Settings.

#include "UIBaseSlot.h"
#include "SlateBrush.h"

void UUIBaseSlot::OnUsed()
{

}

void UUIBaseSlot::SetSlotStyle(UImage & RefImage, UTexture2D * Image)
{
	FSlateBrush Brush;
	if (Image != nullptr)
	{
		Brush.SetResourceObject(Image);
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		Brush.TintColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);

	}
	RefImage.SetBrush(Brush);
}
