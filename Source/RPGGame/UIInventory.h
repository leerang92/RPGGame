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

	// ������ ����Ʈ ����
	void CreateItemList();

	// Slot�� ������ UniformGrid ����
	void SetupGrid(UUniformGridSlot* Slot);

	// ������ �߰�
	void AddItem(FItemInfo NewItem);
	
	// Slot UI Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	TSubclassOf<class UUserWidget> SlotClass;

	// ��ü ������ ����Ʈ ũ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Slot)
	int ListSize;

	// �� ���� ũ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	int ColumnSize;

	// �̹� �ִ� ������ ���� �˻�
	bool IsPresentItem(FItemInfo& NewItem);

protected:
	UPROPERTY()
	class UUniformGridPanel* GridPanel;

private:
	int Column;
	int Row;

	// ������ ������ �迭
	TArray<class UBaseItemSlot*> SlotArr;
};
