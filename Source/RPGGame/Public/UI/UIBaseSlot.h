// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInformation.h"
#include "Image.h"
#include "TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UIBaseSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIBaseSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Slot)
	virtual void OnUsed();
	
protected:
	virtual void SetSlotStyle(UImage& RefImage, UTexture2D* Image);

	UPROPERTY(EditAnywhere, Category = Image, meta = (AllowPrivateAccess = "true"))
	class UImage* SlotImage;
};
