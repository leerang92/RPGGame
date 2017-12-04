// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillInformation.h"
#include "SkillSlot.h"
#include "UI/UIBaseWindow.h"
#include "UISkillBar.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUISkillBar : public UUIBaseWindow
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void CreateSlot();

	// 스킬 사용
	void OnUsedSkill(int Index);
private:

	TArray<USkillSlot*> SlotArr;
};
