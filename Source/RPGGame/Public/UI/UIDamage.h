// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TextBlock.h"
#include "Runtime/UMG/Public/Animation/WidgetAnimation.h"
#include "Blueprint/UserWidget.h"
#include "UIDamage.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API UUIDamage : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetDamage(float NewDamage, FVector TargetVector, bool bCrit = false);

	UPROPERTY(EditAnywhere, Category = Remove)
	float RemoveTime;

	UPROPERTY()
	UTextBlock* DamageText;

	UPROPERTY(BlueprintReadWrite, Category = Animation)
	UWidgetAnimation* TextAnim;

private:
	FTimerHandle RemoveTimer;

	void SetText(float Damage, bool bCrit = false);

	// Remove Widget
	UFUNCTION()
	void OnRemove();

	// float 변수를 소수점이 없는 Text로 변환
	FText GetFloatAsText(float Number);
};
