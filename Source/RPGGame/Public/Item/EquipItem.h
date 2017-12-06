// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "EquipItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AEquipItem : public ABaseItem
{
	GENERATED_BODY()
	
public:

	AEquipItem();

	virtual void OnPickup(APawn* Owner) override;
	
	virtual void OnUsed(APawn* Owner) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY()
	APawn* OwnerPawn;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* AttackFX;

	UParticleSystemComponent* PlayParticle(UParticleSystem* NewFX, FVector SpawnLocation);
};
