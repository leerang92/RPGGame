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

	// 아이템 리스트 생성
	void CreateItemList();

	// Slot을 정리할 UniformGrid 세팅
	void SetupGrid(UUniformGridSlot* Slot);

	// 아이템 추가
	void AddItem(FItemInfo NewItem);
	
	// Slot UI Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	TSubclassOf<class UUserWidget> SlotClass;

	// 전체 아이템 리스트 크기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Slot)
	int ListSize;

	// 한 열의 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slot)
	int ColumnSize;

	// 이미 있는 아이템 여부 검사
	bool IsPresentItem(FItemInfo& NewItem);

protected:
	UPROPERTY()
	class UUniformGridPanel* GridPanel;

private:
	int Column;
	int Row;

	// 슬롯을 저장할 배열
	TArray<class UBaseItemSlot*> SlotArr;
};
