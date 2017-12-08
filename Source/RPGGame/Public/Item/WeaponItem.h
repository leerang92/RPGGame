// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Item/BaseItem.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AWeaponItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AWeaponItem();

	virtual void OnPickup(APawn* Owner) override;

	virtual void OnUsed(APawn* Owner) override;

	UPROPERTY(EditAnywhere, Category = Collider)
	class UCapsuleComponent* WeaponColl;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Information)
	FWeaponInfo WeaponInfo;

	// 무기를 부착할 소켓 이름
	FName AttachPoint;

	APawn* OwnerPawn;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly, Category = Effect)
	TSubclassOf<AEffectActor> EffectClass;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* AttackFX;
};
