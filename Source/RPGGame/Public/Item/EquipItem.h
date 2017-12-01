// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AEquipItem : public ABaseItem
{
	GENERATED_BODY()
	
public:

	virtual void OnPickup(APawn* Owner) override;
	
	virtual void OnUsed(APawn* Owner) override;
};
