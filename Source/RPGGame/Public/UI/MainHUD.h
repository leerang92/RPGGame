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

	/* UI 활성화 및 비활성화 */
	void ActiveInventory();

	void ActiveSkillUI();

	void ActiveGetUI(bool bActive);

protected:
	/* UI 클래스 변수들 */
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
	/* UI Class 반환 */
	FORCEINLINE UUIInventory* GetInventory() const { return InventoryUI; }

	FORCEINLINE UUISkill* GetSkillUI() const { return SkillUI; }

	FORCEINLINE UUIBuffBar* GetBuffBar() const { return BuffBar; }

	FORCEINLINE UUISkillBar* GetSkillBar() const { return SkillBar; }

	FORCEINLINE UUIPlayerState* GetPlayerState() const { return PlayerStateUI; }

private:
	// Inventory UI 활성화 여부
	bool bInventory;

	// Skill UI 활성화 여부
	bool bSkill;

	// 마우스 커서 활성화 함수
	void ShowMouseCursor(bool bShow);

	// 커서 활성화 여부 반환
	bool IsHiddeCursor() const;
};
