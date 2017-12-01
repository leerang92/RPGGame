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
	// Slot ����
	void SetupSlot(FItemInfo Info);

	// Slot�� �̹��� ����
	void SetSlotStyle(UTexture2D* Image);

	// Slot�� ������ ���� �ؽ�Ʈ ����
	void SetAmountText(int Amount);
	
	// �� ���� ���� ��ȯ �Լ�
	bool IsEmpty() const;

	// Slot�� ������ ���
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
