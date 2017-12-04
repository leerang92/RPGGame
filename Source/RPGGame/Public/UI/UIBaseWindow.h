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
	// 전체 행의 크기
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

	// Slot을 Gird Panel의 자식으로 설정
	void SetupGrid(UUserWidget* Slot);
};
