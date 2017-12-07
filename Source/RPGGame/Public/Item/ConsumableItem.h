// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AConsumableItem : public ABaseItem
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void OnPickup(APawn* Owner) override;
	
	virtual void OnUsed(APawn* Owner) override;

protected:
	UPROPERTY(EditAnywhere, Category = Buff, meta = (AllowPrivateAccess = "true"))
	FBuffInfo BuffInfo;
};
