// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Components/UniformGridSlot.h"
#include "Runtime/UMG/Public/Components/UniformGridPanel.h"
#include "BaseItemSlot.h"
#include "Blueprint/UserWidget.h"
#include "UIInventory.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	void CreateItemList();

	void SetupGrid(UUniformGridSlot* Slot);

	void AddItem(FItemInfo NewItem);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	TSubclassOf<class UUserWidget> SlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Slot)
	int ListSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	int ColumnSize;

protected:
	UPROPERTY()
	class UUniformGridPanel* GridPanel;

private:
	int Column;
	int Row;

	TArray<class UBaseItemSlot*> SlotArr;
};
