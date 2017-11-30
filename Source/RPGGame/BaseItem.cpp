// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseItem.h"


// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = MeshComp;
}

void ABaseItem::OnPickup(APawn* Owner)
{
	UE_LOG(LogClass, Warning, TEXT("Pickup Item"));
}

void ABaseItem::OnUsed(APawn* Owner)
{
}

void ABaseItem::OnFouceItem()
{
	MeshComp->SetRenderCustomDepth(true);
}

void ABaseItem::EndFouceItem()
{
	MeshComp->SetRenderCustomDepth(false);
}

