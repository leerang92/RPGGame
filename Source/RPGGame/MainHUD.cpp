// Fill out your copyright notice in the Description page of Project Settings.

#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	bInventory = false;

	// Inventory 숨기기
	if (InventoryUI != nullptr)
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::ActiveInventory()
{
	if (!bInventory) // 인벤토리 활성화
	{
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		bInventory = true;
	}
	else // 인벤토리 비활성화
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
		bInventory = false;
	}
}


