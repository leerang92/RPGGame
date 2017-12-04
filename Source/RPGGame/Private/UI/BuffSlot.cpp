// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffSlot.h"
#include "SlateBrush.h"
#include "UIBuffBar.h"

void UBuffSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GaugePersent -= (InDeltaTime / BuffInfo.Duration);
	GaugePersent = FMath::Max((GaugePersent), 0.0f);

	if (GaugePersent <= 0.0f && ParentWidget)
	{
		UUIBuffBar* BuffBar = Cast<UUIBuffBar>(ParentWidget);
		BuffBar->RemoveSlot(*this);
	}
}

void UBuffSlot::SetSlot(FBuffInfo& Info, UUserWidget* Parent)
{
	BuffInfo = Info;
	GaugePersent = 1.0f;
	ParentWidget = Parent;
	//SetSlotStyle(*SlotImage, BuffInfo.Image);
}

void UBuffSlot::SetDuration(float Duration)
{
	if (Duration > 0)
	{
		GaugePersent = 1.0f;
		//BuffInfo.Duration = Duration;
	}
}
