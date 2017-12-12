// Fill out your copyright notice in the Description page of Project Settings.

#include "UISkillAttack.h"
#include "SlateBrush.h"

void UUISkillAttack::NativeConstruct()
{
	Super::NativeConstruct();

	bIsUseSkill = true;
	CurrentPersent = 0.0f;

	SetProgressBarStyle(SkillInfo.Image);
}

void UUISkillAttack::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurrentPersent > 0.0f)
	{
		const float Persent = ((CurrentPersent / SkillInfo.CoolTime) * 100.0f) / 100.0f;
		SkillBar->SetPercent(Persent);
		CurrentPersent -= InDeltaTime / 10.0f;
	}
	else
	{
		bIsUseSkill = true;
	}
}

void UUISkillAttack::OnUsed()
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(GetOwningPlayerPawn());
	if (PC && PC->IsAttack() && bIsUseSkill)
	{
		PC->SetSkill(SkillInfo);
		bIsUseSkill = false;
		CurrentPersent = SkillInfo.CoolTime;
	}
}

void UUISkillAttack::SetProgressBarStyle(UTexture2D * Image)
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
	SkillBar->WidgetStyle = Style;
}



