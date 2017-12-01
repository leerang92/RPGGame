// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsumableItem.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AHealthPotion : public AConsumableItem
{
	GENERATED_BODY()
	
public:

	virtual void OnUsed(APawn* Owner) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	float HP;
};
