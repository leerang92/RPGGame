// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillInformation.h"
#include "ProgressBar.h"
#include "UI/BaseTouchBottun.h"
#include "UISkillAttack.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUISkillAttack : public UBaseTouchBottun
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = UI)
	virtual void OnUsed() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInformation)
	FSkillInfo SkillInfo;
	
protected:
	UPROPERTY()
	UProgressBar* SkillBar;

	float CurrentPersent;

	bool bIsUseSkill;

	void SetProgressBarStyle(UTexture2D * Image);
};
