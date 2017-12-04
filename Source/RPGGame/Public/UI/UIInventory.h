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

	// 아이템 리스트 생성
	void CreateItemList();

	// 아이템 추가
	void AddItem(FItemInfo NewItem);

	// 전체 아이템 리스트 크기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Slot)
	int ListSize;

	// 이미 있는 아이템 여부 검사
	bool IsPresentItem(FItemInfo& NewItem);

private:
	// 슬롯을 저장할 배열
	TArray<class UUIInventorySlot*> SlotArr;
};
