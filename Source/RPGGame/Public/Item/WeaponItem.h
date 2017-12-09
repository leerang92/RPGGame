// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "EffectActor.h"
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

	// 무기 콜리더 (무기 충돌 처리를 위한)
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

	// 이미 데미지를 준 액터 배열
	TArray<AActor*> TakeDamageActors;
public:
	UPROPERTY(EditDefaultsOnly, Category = Effect)
	TSubclassOf<AEffectActor> EffectClass;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* AttackFX;

	// 데미지를 줄 수 있는 액터 여부 반환
	bool IsTakeDamage(AActor& GetActor) const;

	// 오버랩 된 액터 배열 초기화
	void SetResetActorArray();

	/* 사운드 */
	void PlaySound(USoundCue * Sound);
};
