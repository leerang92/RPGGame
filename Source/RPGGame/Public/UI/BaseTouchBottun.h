// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "Image.h"
#include "Blueprint/UserWidget.h"
#include "BaseTouchBottun.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBaseTouchBottun : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void OnUsed();

	virtual void EndUsed();
	
protected:
	UPROPERTY()
	UImage* SlotImage;
};
