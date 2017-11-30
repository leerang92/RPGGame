// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInformation.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class RPGGAME_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* MeshComp;

	virtual void OnPickup(APawn* Owner);

	virtual void OnUsed(APawn* Owner);

	void OnFouceItem();

	void EndFouceItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Information)
	FItemInfo Info;
};
