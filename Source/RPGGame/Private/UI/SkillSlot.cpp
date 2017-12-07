// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillSlot.h"
#include "SlateBrush.h"
#include "RPGCharacter.h"

void USkillSlot::NativeConstruct()
{
	Super::NativeConstruct();
	bDrop = false;
	bUsed = true;
	bIsUseSkill = true;

	CurrentPersent = 0.0f;

	SetProgressBarStyle(SkillInfo.Image);
	//SetSlotStyle(*SlotImage, SkillInfo.Image);
}

void USkillSlot::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentPersent > 0.0f)
	{
		const float Persent = ((CurrentPersent / SkillInfo.CoolTime) * 100.0f) / 100.0f;
		SlotBar->SetPercent(Persent);
		CurrentPersent -= InDeltaTime / 10.0f;
	}
	else
	{
		bIsUseSkill = true;
	}
}

void USkillSlot::OnUsed()
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(GetOwningPlayerPawn());
	if (PC && bIsUseSkill)
	{
		PC->SetSkill(SkillInfo);
		bIsUseSkill = false;
		CurrentPersent = SkillInfo.CoolTime;
	}
}

void USkillSlot::SetSlot(FSkillInfo Info)
{
	SkillInfo = Info;

	SetProgressBarStyle(SkillInfo.Image);
	//SetSlotStyle(*SlotImage, SkillInfo.Image);
}

void USkillSlot::SetDrop(bool isDrop)
{
	bDrop = isDrop;
}

void USkillSlot::SetProgressBarStyle(UTexture2D * Image)
{
	FSlateBrush Brush;
	if (Image == nullptr)
	{
		Brush.TintColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		Brush.SetResourceObject(Image);
		Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	FProgressBarStyle Style;
	Style.BackgroundImage = Brush;
	SlotBar->WidgetStyle = Style;
}
