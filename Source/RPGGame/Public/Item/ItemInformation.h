// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "ItemInformation.generated.h"

class ABaseItem;

UENUM(BlueprintType)
enum EItemType
{
	NONE,
	WEAPON,
	EQUIPMENT,
	SUPPLIES,
};

// ������ ����(����, �Ҹ��� ����)
USTRUCT(BlueprintType)
struct FItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Item)
	FName Name;

	UPROPERTY(EditAnywhere, Category = Item)
	int32 Amount;

	UPROPERTY(EditAnywhere, Category = Item)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, Category = Item)
	FName Context;

	UPROPERTY(EditAnywhere, Category = Item)
	float DropRate;

	UPROPERTY(EditAnywhere, Category = Item)
	TEnumAsByte<EItemType> Type;

	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<class ABaseItem> ItemClass;

public:
	FItemInfo() :
		Name(TEXT("No Name")),
		Amount(0),
		Image(nullptr),
		Context(TEXT("No Context")),
		Type(EItemType::NONE),
		ItemClass(nullptr)
	{}
	// ������ ��� ����
	bool IsDropItem()
	{
		float Rate = FMath::Fmod(FMath::FRand(), 100.0f) * 100.0f;
		return DropRate > Rate;
	}
};

// ���� ������ ����
USTRUCT()
struct FWeaponInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Weapon)
	float MaxDamage;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float MinDamage;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CriticalRate;

	UPROPERTY(EditAnywhere, Category = Weapon)
	float CriticalDamageRate;

	UPROPERTY(EditAnywhere, Category = Weapon)
	USoundCue* Sound;

public:
	FWeaponInfo() :
		MaxDamage(0),
		MinDamage(0),
		CriticalRate(1),
		Sound(nullptr)
	{}

	// ũ��Ƽ�� �������� �����Ͽ� ������ ����
	float GetDamage()
	{
		float Rate = FMath::Fmod(FMath::FRand(), 100.0f) * 100.0f;
		if (CriticalRate > Rate)
		{
			bIsCritical = true;
			return GetDamageRange() * CriticalDamageRate;
		}
		else
		{
			bIsCritical = false;
			return GetDamageRange();
		}
	}

	bool IsCritical() const
	{
		return bIsCritical;
	}

private:
	bool bIsCritical = false;

	float GetDamageRange()
	{
		return FMath::RandRange(MinDamage, MaxDamage);
	}
};

// ���� ����
USTRUCT()
struct FPotionInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Potion)
	float EffectValue;

	UPROPERTY(EditAnywhere, Category = Potion)
	float Duration;

public:
	FPotionInfo() :
		EffectValue(0),
		Duration(0)
	{}
};

// ���� ����
USTRUCT(BlueprintType)
struct FBuffInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Buff)
	FName Name;

	UPROPERTY(EditAnywhere, Category = Buff)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, Category = Buff)
	float Duration;

public:
	FBuffInfo() :
		Name(TEXT("NoName")),
		Image(nullptr),
		Duration(0.0f)
	{}
};