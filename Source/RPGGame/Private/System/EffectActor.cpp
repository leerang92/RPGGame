// Fill out your copyright notice in the Description page of Project Settings.

#include "EffectActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEffectActor::AEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UParticleSystem* SpawnFX = GetParticle(Type);
	if (SpawnFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, SpawnFX, GetActorLocation(), GetActorRotation());
	}
}

UParticleSystem * AEffectActor::GetParticle(EEffectType Type) const
{
	switch (Type)
	{
	case EEffectType::BLOOD:
		return MonsterBloodFX;
	case EEffectType::HIT:
		return HitFX;
	}
	return nullptr;
}
