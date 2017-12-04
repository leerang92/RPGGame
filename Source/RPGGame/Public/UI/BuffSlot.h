// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBaseSlot.h"
#include "BuffSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBuffSlot : public UUIBaseSlot
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetSlot(FBuffInfo& Info, UUserWidget* Parent);

	void SetDuration(float Duration);

	UFUNCTION(BlueprintCallable, Category = Slot)
	FORCEINLINE UImage* GetImage() const { return SlotImage; }

	UFUNCTION(BlueprintCallable, Category = Slot)
	FORCEINLINE UTexture2D* GetTexture() const { return BuffInfo.Image; }

	FORCEINLINE FBuffInfo GetBuffInfo() const { return BuffInfo; }
	
	UPROPERTY(BlueprintReadWrite, Category = Gauge)
	float GaugePersent;

private:
	FBuffInfo BuffInfo;

	UUserWidget* ParentWidget;
};
