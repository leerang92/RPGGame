// Fill out your copyright notice in the Description page of Project Settings.

#include "UIBaseWindow.h"

void UUIBaseWindow::SetupGrid(UUserWidget* Slot)
{
	if (Slot == nullptr)
		return;

	UUniformGridSlot* GridSlot = GridPanel->AddChildToUniformGrid(Slot);

	// Slot ����
	GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	GridSlot->SetColumn(Column);
	GridSlot->SetRow(Row);

	// ��, �� ����
	++Column;
	if (Column >= ColumnSize)
	{
		Column = 0;
		++Row;
	}
}

