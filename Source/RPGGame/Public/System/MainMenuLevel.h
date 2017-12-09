// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevel.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AMainMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> MainUIClass;
};
