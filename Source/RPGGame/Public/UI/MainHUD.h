// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInventory.h"
#include "UIBuffBar.h"
#include "UISkill.h"
#include "UISkillBar.h"
#include "UIPlayerState.h"
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

	/* UI Ȱ��ȭ �� ��Ȱ��ȭ */
	void ActiveInventory();

	void ActiveSkillUI();

	void ActiveGetUI(bool bActive);

protected:
	/* UI Ŭ���� ������ */
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

	UPROPERTY()
	class UUIPlayerState* PlayerStateUI;

public:
	/* UI Class ��ȯ */
	FORCEINLINE UUIInventory* GetInventory() const { return InventoryUI; }

	FORCEINLINE UUISkill* GetSkillUI() const { return SkillUI; }

	FORCEINLINE UUIBuffBar* GetBuffBar() const { return BuffBar; }

	FORCEINLINE UUISkillBar* GetSkillBar() const { return SkillBar; }

	FORCEINLINE UUIPlayerState* GetPlayerState() const { return PlayerStateUI; }

private:
	// Inventory UI Ȱ��ȭ ����
	bool bInventory;

	// Skill UI Ȱ��ȭ ����
	bool bSkill;

	// ���콺 Ŀ�� Ȱ��ȭ �Լ�
	void ShowMouseCursor(bool bShow);

	// Ŀ�� Ȱ��ȭ ���� ��ȯ
	bool IsHiddeCursor() const;
};
