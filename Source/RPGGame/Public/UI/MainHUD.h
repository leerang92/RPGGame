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

	// Inventory Ȱ��ȭ �Լ�
	void ActiveInventory();

	FORCEINLINE UUIInventory* GetInventory() const { return InventoryUI; }

	// Skill â Ȱ��ȭ
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
	// Inventory Ȱ��ȭ ����
	bool bInventory;

	bool bSkill;
	// ���콺 Ŀ�� Ȱ��ȭ
	void ShowMouseCursor(bool bShow);

	// Ŀ�� Ȱ��ȭ ����
	bool IsHiddeCursor() const;
};
