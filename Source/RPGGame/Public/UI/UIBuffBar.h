// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInformation.h"
#include "BuffSlot.h"
#include "UI/UIBaseWindow.h"
#include "UIBuffBar.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIBuffBar : public UUIBaseWindow
{
	GENERATED_BODY()
	
public:
	// ���� ������ ����
	void SetBuffIcon(FBuffInfo Info);

	// ���� �ߺ� ���� Ȯ�� �� �ߺ� �� ���� �ð��� �ʱ�ȭ
	bool IsPresentBuff(FBuffInfo& Info);

	// ������ ���� Slot ���� �Լ�
	void RemoveSlot(UBuffSlot& RemoveSlot);

private:
	// UniformGridPanel �缳��
	void RelocationGrid();

	TArray<class UBuffSlot*> SlotArr;
};
