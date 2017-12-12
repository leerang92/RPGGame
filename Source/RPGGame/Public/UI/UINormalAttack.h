// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseTouchBottun.h"
#include "UINormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUINormalAttack : public UBaseTouchBottun
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = UI)
	virtual void OnUsed() override;

	UFUNCTION(BlueprintCallable, Category = UI)
	virtual void EndUsed() override;
	
	
};
