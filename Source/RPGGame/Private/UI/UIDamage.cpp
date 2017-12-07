// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDamage.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

void UUIDamage::SetDamage(float NewDamage, FVector TargetVector)
{
	UE_LOG(LogClass, Warning, TEXT("!!!"));
	APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Con)
	{
		// Ÿ���� ���� ��ǥ�� ��ũ�� ��ǥ�� ��ȯ
		FVector2D ScreenVector;
		Con->ProjectWorldLocationToScreen(TargetVector, ScreenVector);

		// ���� �� ������ ��ǥ�� ���ϱ�
		float rX = FMath::RandRange(-50.0f, 50.0f);
		float rY = FMath::RandRange(-50.0f, 50.0f);

		// UI ��ġ ����
		ScreenVector += FVector2D(rX, rY);
		SetPositionInViewport(ScreenVector);

		SetText(NewDamage);
		PlayAnimation(TextAnim);

		// RemoveTime ���Ŀ� ���� ����
		FLatentActionInfo Info;
		Info.CallbackTarget = this;
		Info.ExecutionFunction = "OnRemove";
		Info.Linkage = 1;
		UKismetSystemLibrary::Delay(this, RemoveTime, Info);
	}
}

void UUIDamage::SetText(float Damage)
{
	DamageText->SetText(GetFloatAsText(Damage));
}

void UUIDamage::OnRemove()
{
	this->RemoveFromViewport();
}

FText UUIDamage::GetFloatAsText(float Number)
{
	float Rounded = roundf(Number);
	if (FMath::Abs(Number - Rounded) < FMath::Pow(10, -1 * 0))
	{
		Number = Rounded;
	}
	FNumberFormattingOptions NumberFormat;
	NumberFormat.MinimumIntegralDigits = 1;
	NumberFormat.MaximumIntegralDigits = 100000;
	NumberFormat.MinimumFractionalDigits = false;
	NumberFormat.MaximumFractionalDigits = false;

	return FText::AsNumber(Number, &NumberFormat);
}
