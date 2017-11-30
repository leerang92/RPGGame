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

	void SetupSlot(FItemInfo Info);

	void SetSlotStyle(UTexture2D* Image);

	void SetAmountText(int Amount);
	
	bool IsEmpty() const;

protected:
	FItemInfo ItemInfo;

	UPROPERTY()
	UImage* ItemImage;

	UPROPERTY()
	UTextBlock* AmountText;
};
