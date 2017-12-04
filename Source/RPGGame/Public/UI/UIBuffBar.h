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
	// 버프 아이콘 설정
	void SetBuffIcon(FBuffInfo Info);

	// 버프 중복 여부 확인 및 중복 시 지속 시간만 초기화
	bool IsPresentBuff(FBuffInfo& Info);

	// 버프가 끝난 Slot 삭제 함수
	void RemoveSlot(UBuffSlot& RemoveSlot);

private:
	// UniformGridPanel 재설정
	void RelocationGrid();

	TArray<class UBuffSlot*> SlotArr;
};
