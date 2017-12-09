// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RPGGameGameMode.h"
#include "RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameGameMode::ARPGGameGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprint/Player/BP_RPGCharacter.BP_RPGCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
