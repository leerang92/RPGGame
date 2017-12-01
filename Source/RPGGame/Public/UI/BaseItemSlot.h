// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInformation.h"
#include "SlateBrush.h"
#include "Image.h"
#include "TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "BaseItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBaseItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Slot 세팅
	void SetupSlot(FItemInfo Info);

	// Slot의 이미지 세팅
	void SetSlotStyle(UTexture2D* Image);

	// Slot의 아이템 갯수 텍스트 세팅
	void SetAmountText(int Amount);
	
	// 빈 슬롯 여부 반환 함수
	bool IsEmpty() const;

	// Slot의 아이템 사용
	UFUNCTION(BlueprintCallable, Category = Item)
	void UseSlotItem();

	FORCEINLINE FItemInfo GetItemInfo() const { return ItemInfo; }

protected:
	FItemInfo ItemInfo;

	UPROPERTY()
	UImage* ItemImage;

	UPROPERTY()
	UTextBlock* AmountText;
};
