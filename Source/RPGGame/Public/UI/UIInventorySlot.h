// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBaseSlot.h"
#include "UIInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIInventorySlot : public UUIBaseSlot
{
	GENERATED_BODY()
	
public:
	void SetupSlot(FItemInfo Info);

	// ΩΩ∑‘¿« ∫Û ø©∫Œ π›»Ø
	FORCEINLINE bool IsEmpty() const { return ItemInfo.Image == nullptr; }

	FORCEINLINE FItemInfo GetItemInfo() const { return ItemInfo; }

protected:
	virtual void OnUsed() override;
	
private:
	FItemInfo ItemInfo;

	UPROPERTY()
	class UTextBlock* AmountText;

	void SetAmountText(int Amount);
};
