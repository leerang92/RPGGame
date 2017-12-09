// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuLevel.h"
#include "UserWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

void AMainMenuLevel::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Menu = CreateWidget<UUserWidget>(GetWorld(), MainUIClass);
	check(Menu);
	Menu->AddToViewport();

	APlayerController* Con = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Con)
	{
		Con->bShowMouseCursor = true;
	}
}
