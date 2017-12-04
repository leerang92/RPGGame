// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillInformation.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInformation)
	FSkillInfo SkillInfo;
	
	virtual void NativeConstruct() override;

	virtual void OnUsed() override;

	// ���� ����
	UFUNCTION(BlueprintCallable, Category = Slot)
	void SetSlot(FSkillInfo Info);

	// ���� �̹��� ��ȯ
	UFUNCTION(BlueprintCallable, Category = Slot)
	FORCEINLINE UTexture2D* GetSlotImage() const { return SkillInfo.Image; }
	
	// Slot Drop ���� ���� ��ȯ
	UFUNCTION(BlueprintCallable, Category = Slot)
	FORCEINLINE bool IsDrop() const { return bDrop; }

	void SetDrop(bool isDrop);

	// ��ų ��� ���� ���� ��ȯ
	FORCEINLINE bool IsUseSkill() const { return bUsed; }

private:
	bool bDrop;

	// ��ų ��� ���� ����
	bool bUsed;
};
