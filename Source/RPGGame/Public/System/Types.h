// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.generated.h"

UENUM(BlueprintType)
enum EAIState
{
	IDLE,
	WANDER,
	MOVE,
	AGRO,
	ATTACK,
	DIE,
};

UENUM(BlueprintType)
enum EEffectType
{
	BLOOD,
	HIT,
};
