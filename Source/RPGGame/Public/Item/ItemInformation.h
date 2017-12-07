// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	float MaximumDropRate = 100.0f;

public:
	FItemInfo() :
		Name(TEXT("No Name")),
		Amount(0),
		Image(nullptr),
		Context(TEXT("No Context")),
		Type(EItemType::NONE),
		ItemClass(nullptr)
	{}

	bool IsDropItem()
	{
		float Rate = FMath::Fmod(FMath::FRand(), MaximumDropRate) * 100.0f;
		UE_LOG(LogClass, Warning, TEXT("%f"), Rate);
		return DropRate > Rate;
		//Rate %= MaximumDropRate;
	}

};

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