// Fill out your copyright notice in the Description page of Project Settings.

#include "UIBaseWindow.h"

void UUIBaseWindow::SetupGrid(UUserWidget* Slot)
{
	if (Slot == nullptr)
		return;

	UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(Slot);

	// Slot 설정
	GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	GridSlot->SetColumn(Column);
	GridSlot->SetRow(Row);

	// 행, 열 증가
	++Column;
	if (Column >= ColumnSize)
	{
		Column = 0;
		++Row;
	}
}

