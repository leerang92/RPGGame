// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BaseMonster.h"
#include "MasterGrunt.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API AMasterGrunt : public ABaseMonster
{
	GENERATED_BODY()
	
public:
	AMasterGrunt();

	virtual void Tick(float DeltaTime) override;

	/* Weapon */
	UPROPERTY(EditAnywhere, Category = SkeletalMesh)
	UStaticMeshComponent* RWeaponMesh;

	UPROPERTY(EditAnywhere, Category = SkeletalMesh)
	UStaticMeshComponent* LWeaponMesh;

	UPROPERTY(EditAnywhere, Category = Collider)
	UCapsuleComponent* RWeaponColl;

	UPROPERTY(EditAnywhere, Category = Collider)
	UCapsuleComponent* LWeaponColl;

protected:
	/* 충돌 처리 */
	UFUNCTION()
	virtual void OnMeleeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION()
	virtual void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
private:
	/* Weapon Socket Name */
	FName RWeaponSocketName;
	FName LWeaponSocketName;
	
};
