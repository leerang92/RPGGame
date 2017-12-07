// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacter.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UCharacterAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION()
	void AnimNotify_NextAttack(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_StopAttack(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_CamShake(UAnimNotify* Notify);

	UFUNCTION()
	void AnimNotify_SlowMotion(UAnimNotify* Notify);
	
protected:
	class ARPGCharacter* PC;
};
