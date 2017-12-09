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

	UPROPERTY(EditAnywhere, Category = Level)
	FName NextLevelName;
	
protected:
	UPROPERTY()
	UButton* BtnPlayGame;

	UPROPERTY()
	UButton* BtnExitGame;
	
	UFUNCTION()
	void OnClickPlayGame();

	UFUNCTION()
	void OnClickExitGame();
};
