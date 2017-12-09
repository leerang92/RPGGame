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
	// ǥ���� ���� ���� �� ���� ����
	void SetDamage(float NewDamage, FVector TargetVector, bool bCrit = false);

	// ���� ���� ��� �ð�
	UPROPERTY(EditAnywhere, Category = Remove)
	float RemoveTime;

	UPROPERTY()
	UTextBlock* DamageText;

	UPROPERTY(BlueprintReadWrite, Category = Animation)
	UWidgetAnimation* TextAnim;

private:
	FTimerHandle RemoveTimer;

	void SetText(float Damage, bool bCrit = false);

	// ���� ����
	UFUNCTION()
	void OnRemove();

	// float ������ �Ҽ����� ���� Text�� ��ȯ
	FText GetFloatAsText(float Number);
};
