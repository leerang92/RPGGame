// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Button.h"
#include "Blueprint/UserWidget.h"
#include "UIMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	// 넘어갈 레벨 이름
	UPROPERTY(EditAnywhere, Category = Level)
	FName NextLevelName;
	
protected:
	UPROPERTY()
	UButton* BtnPlayGame;

	UPROPERTY()
	UButton* BtnExitGame;
	
	// 플레이 게임 버튼 클릭시 호출
	UFUNCTION()
	void OnClickPlayGame();

	// ExitGame 버튼 클릭시 호출
	UFUNCTION()
	void OnClickExitGame();
};
