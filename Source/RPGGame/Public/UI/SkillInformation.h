// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "SkillInformation.generated.h"

USTRUCT(BlueprintType)
struct FSkillInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	UAnimMontage* SkillAnim;

public:
	FSkillInfo() :
		Name(TEXT("No Name")),
		Damage(1.0f),
		CoolTime(1.0f),
		Image(nullptr),
		SkillAnim(nullptr)
	{}
};