// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

UCLASS(ABSTRACT, Blueprintable)
class RPGGAME_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectActor();
	
	virtual void PostInitializeComponents() override;

	// 파티클 타입 얻기
	UParticleSystem* GetParticle(EEffectType Type) const;

	// 파티클 타입 정보
	EEffectType Type;

	UPROPERTY(EditDefaultsOnly, Category = Effect)
	UParticleSystem* MonsterBloodFX;
	
	UPROPERTY(EditDefaultsOnly, Category = Effect)
	UParticleSystem* HitFX;

};
