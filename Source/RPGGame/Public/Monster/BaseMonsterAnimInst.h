// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "Animation/AnimInstance.h"
#include "BaseMonsterAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UBaseMonsterAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION()
	void AnimNotify_NextAttack(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_StartAttack(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_EndAttack(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_StopAttack(UAnimNotify* Notify);
	
protected:
	class ABaseMonster* Monster;
};
