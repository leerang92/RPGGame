// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInventorySlot.h"
#include "UI/UIBaseWindow.h"
#include "UIInventory.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIInventory : public UUIBaseWindow
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	// ������ ����Ʈ ����
	void CreateItemList();

	// ������ �߰�
	void AddItem(FItemInfo NewItem);

	// ��ü ������ ����Ʈ ũ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Slot)
	int ListSize;

	// �̹� �ִ� ������ ���� �˻�
	bool IsPresentItem(FItemInfo& NewItem);

private:
	// ������ ������ �迭
	TArray<class UUIInventorySlot*> SlotArr;
};
