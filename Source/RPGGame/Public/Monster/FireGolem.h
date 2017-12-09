// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BaseMonster.h"
#include "FireGolem.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AFireGolem : public ABaseMonster
{
	GENERATED_BODY()
	
public:

	AFireGolem();

	UFUNCTION()
	virtual void OnMeleeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditAnywhere, Category = SkeletalMesh)
	USkeletalMeshComponent* WeaponMesh;

protected:
	void StopAgro();

private:
	FName WeaponSocketName;
};
