// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInventory.h"
#include "UIBuffBar.h"
#include "UISkill.h"
#include "UISkillBar.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;

	// Inventory 활성화 함수
	void ActiveInventory();

	FORCEINLINE UUIInventory* GetInventory() const { return InventoryUI; }

	// Skill 창 활성화
	void ActiveSkillUI();

	FORCEINLINE UUISkill* GetSkillUI() const { return SkillUI; }

	FORCEINLINE UUIBuffBar* GetBuffBar() const { return BuffBar; }

	FORCEINLINE UUISkillBar* GetSkillBar() const { return SkillBar; }

	void ActiveGetUI(bool bActive);

protected:
	// Inventory Class
	UPROPERTY()
	class UUIInventory* InventoryUI;

	UPROPERTY()
	class UUIBuffBar* BuffBar;

	UPROPERTY()
	class UUISkill* SkillUI;

	UPROPERTY()
	class UUISkillBar* SkillBar;

	UPROPERTY()
	class UUserWidget* GetUI;

private:
	// Inventory 활성화 여부
	bool bInventory;

	bool bSkill;
	// 마우스 커서 활성화
	void ShowMouseCursor(bool bShow);

	// 커서 활성화 여부
	bool IsHiddeCursor() const;
};
