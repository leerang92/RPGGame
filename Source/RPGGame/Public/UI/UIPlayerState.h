// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "UIPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIPlayerState : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	void SetHP(float NewHP);

	void SetMana(float NewMana);
	
	UPROPERTY(EditAnywhere)
	UProgressBar* HPBar;

	UPROPERTY()
	UProgressBar* ManaBar;
	
	UPROPERTY(EditAnywhere)
	float MaxHP;

	float MaxMana;
};
