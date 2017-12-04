// Fill out your copyright notice in the Description page of Project Settings.

#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	bInventory = false;
	bSkill = false;

	// Inventory 숨기기
	if (InventoryUI != nullptr)
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SkillUI != nullptr)
	{
		SkillUI->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GetUI != nullptr)
	{
		GetUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::ActiveInventory()
{
	if (!bInventory) // 인벤토리 활성화
	{
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		ShowMouseCursor(true);
		bInventory = true;
	}
	else // 인벤토리 비활성화
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
		ShowMouseCursor(false);
		bInventory = false;
	}
}

void UMainHUD::ActiveSkillUI()
{
	if (!bSkill)
	{
		SkillUI->SetVisibility(ESlateVisibility::Visible);
		ShowMouseCursor(true);
		bSkill = true;
	}
	else
	{
		SkillUI->SetVisibility(ESlateVisibility::Hidden);
		ShowMouseCursor(false);
		bSkill = false;
	}
}

void UMainHUD::ActiveGetUI(bool bActive)
{
	if (bActive)
	{
		GetUI->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GetUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::ShowMouseCursor(bool bShow)
{
	APlayerController* Con = GetWorld()->GetFirstPlayerController();
	check(Con);

	if (bShow)
	{
		Con->bShowMouseCursor = true;
	}
	else if (!bShow && !IsHiddeCursor())
	{
		Con->bShowMouseCursor = false;
	}
}

bool UMainHUD::IsHiddeCursor() const
{
	return bInventory && bSkill;
}


