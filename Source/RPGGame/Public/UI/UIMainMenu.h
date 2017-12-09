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

	// �Ѿ ���� �̸�
	UPROPERTY(EditAnywhere, Category = Level)
	FName NextLevelName;
	
protected:
	UPROPERTY()
	UButton* BtnPlayGame;

	UPROPERTY()
	UButton* BtnExitGame;
	
	// �÷��� ���� ��ư Ŭ���� ȣ��
	UFUNCTION()
	void OnClickPlayGame();

	// ExitGame ��ư Ŭ���� ȣ��
	UFUNCTION()
	void OnClickExitGame();
};
