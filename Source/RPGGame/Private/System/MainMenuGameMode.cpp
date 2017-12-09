// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameMode.h"


void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogClass, Warning, TEXT("Set Game Mode"));
}

