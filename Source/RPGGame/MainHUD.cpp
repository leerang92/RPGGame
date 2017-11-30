// Fill out your copyright notice in the Description page of Project Settings.

#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	bInventory = false;

	// Inventory �����
	if (InventoryUI != nullptr)
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainHUD::ActiveInventory()
{
	if (!bInventory) // �κ��丮 Ȱ��ȭ
	{
		InventoryUI->SetVisibility(ESlateVisibility::Visible);
		bInventory = true;
	}
	else // �κ��丮 ��Ȱ��ȭ
	{
		InventoryUI->SetVisibility(ESlateVisibility::Hidden);
		bInventory = false;
	}
}


