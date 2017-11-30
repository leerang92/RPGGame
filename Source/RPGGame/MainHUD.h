// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIInventory.h"
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

	FORCEINLINE UUIInventory* GetInventory() const { return InventoryUI; }

	// Inventory Ȱ��ȭ �Լ�
	void ActiveInventory();

protected:
	// Inventory Class
	UPROPERTY()
	class UUIInventory* InventoryUI;

private:
	// Inventory Ȱ��ȭ ����
	bool bInventory;

};
