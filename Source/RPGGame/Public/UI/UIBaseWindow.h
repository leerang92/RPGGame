// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Components/UniformGridSlot.h"
#include "Runtime/UMG/Public/Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "UIBaseWindow.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIBaseWindow : public UUserWidget
{
	GENERATED_BODY()

public:
	// ��ü ���� ũ��
	UPROPERTY(EditAnywhere, Category = Gird)
	int ColumnSize;

	// Slot UI Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	TSubclassOf<class UUserWidget> SlotClass;

protected:
	int Row;
	int Column;

	UPROPERTY()
	class UUniformGridPanel* GridPanel;

	// Slot�� Gird Panel�� �ڽ����� ����
	void SetupGrid(UUserWidget* Slot);
};
