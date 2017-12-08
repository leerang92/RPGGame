// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillInformation.h"
#include "ProgressBar.h"
#include "UI/UIBaseSlot.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API USkillSlot : public UUIBaseSlot
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void OnUsed() override;

	// 슬롯 설정
	UFUNCTION(BlueprintCallable, Category = Slot)
	void SetSlot(FSkillInfo Info);

	// 슬롯 이미지 반환
	UFUNCTION(BlueprintCallable, Category = Slot)
	FORCEINLINE UTexture2D* GetSlotImage() const { return SkillInfo.Image; }
	
	// Slot Drop 가능 여부 반환
	UFUNCTION(BlueprintCallable, Category = Slot)
	FORCEINLINE bool IsDrop() const { return bDrop; }

	void SetDrop(bool isDrop);

	// 스킬 사용 가능 여부 반환
	FORCEINLINE bool IsUseSkill() const { return bUsed && SkillInfo.Image != nullptr; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInformation)
	FSkillInfo SkillInfo;

protected:
	UPROPERTY()
	UProgressBar* SlotBar;

	void SetProgressBarStyle(UTexture2D* Image);

	float CurrentPersent;

	bool bIsUseSkill;

private:
	// 슬롯에 아이콘 드랍 가능 여부
	bool bDrop;

	// 스킬 사용 가능 여부
	bool bUsed;
};
