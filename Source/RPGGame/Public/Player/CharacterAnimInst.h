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
	
	// 다음 공격 여부
	UFUNCTION()
	void AnimNotify_NextAttack(UAnimNotify* Notify);

	// 공격 중지
	UFUNCTION()
	void AnimNotify_StopAttack(UAnimNotify* Notify);

	// 카메라 흔들기
	UFUNCTION()
	void AnimNotify_CamShake(UAnimNotify* Notify);

	// 슬로우 모션
	UFUNCTION()
	void AnimNotify_SlowMotion(UAnimNotify* Notify);

	// 발자국 소리 생성
	UFUNCTION()
	void AnimNotify_MakeNoise(UAnimNotify* Notify);
	
protected:
	class ARPGCharacter* PC;
};
