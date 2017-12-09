// Fill out your copyright notice in the Description page of Project Settings.

#include "UIMainMenu.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UUIMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	BtnPlayGame->OnClicked.AddDynamic(this, &UUIMainMenu::OnClickPlayGame);
	BtnExitGame->OnClicked.AddDynamic(this, &UUIMainMenu::OnClickExitGame);

	NextLevelName = TEXT("InGameMap");
}

void UUIMainMenu::OnClickPlayGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
}

void UUIMainMenu::OnClickExitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
