// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInformation.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class ARPGGameCharacter;

UCLASS()
class RPGGAME_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* MeshComp;

	// 아이템 습득
	virtual void OnPickup(APawn* Owner);

	// 아이템 사용
	virtual void OnUsed(APawn* Owner);

	// 아이템이 포커싱 되었을 때
	void OnFouceItem();

	// 아이템이 포커싱이 아닐 때
	void EndFouceItem();

	// 아이템 정보
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Information)
	FItemInfo Info;
};
