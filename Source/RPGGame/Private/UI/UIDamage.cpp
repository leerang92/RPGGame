// Fill out your copyright notice in the Description page of Project Settings.

#include "UIDamage.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

void UUIDamage::SetDamage(float NewDamage, FVector TargetVector)
{
	APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Con)
	{
		FVector2D ScreenVector;
		Con->ProjectWorldLocationToScreen(TargetVector, ScreenVector);

		float rX = FMath::RandRange(-50.0f, 50.0f);
		float rY = FMath::RandRange(-50.0f, 50.0f);

		ScreenVector += FVector2D(rX, rY);
		SetPositionInViewport(ScreenVector);

		SetText(NewDamage);

		PlayAnimation(TextAnim);
	
		// RemoveTime 이후에 위젯 삭제
		FLatentActionInfo Info;
		Info.CallbackTarget = this;
		Info.ExecutionFunction = "OnRemove";
		Info.Linkage = 1;
		UKismetSystemLibrary::Delay(this, RemoveTime, Info);
	}
}

void UUIDamage::SetText(float Damage)
{
	DamageText->SetText(FText::AsNumber(Damage));
}

void UUIDamage::OnRemove()
{
	this->RemoveFromViewport();
}
