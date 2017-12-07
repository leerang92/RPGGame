// Fill out your copyright notice in the Description page of Project Settings.

#include "FireGolem.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

AFireGolem::AFireGolem()
{
	WeaponSocketName = TEXT("Weapon_Hand_r");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Weapon(TEXT("SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Golem/SK_Enemy_Golem01_Weapon.SK_Enemy_Golem01_Weapon'"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetSkeletalMesh(SK_Weapon.Object);
}

void AFireGolem::OnAgroOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp)
	{
		ARPGCharacter* PC = Cast<ARPGCharacter>(OtherActor);
		if (PC)
		{
			MonsterCon->SetTargetPawn(PC);
			AIState = EAIState::AGRO;
			MonsterCon->SetAIState(AIState);
			GetWorldTimerManager().SetTimer(WaitTimer, this, &AFireGolem::StopAgro, 2.333f);
		}
	}
}

void AFireGolem::OnMeleeOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void AFireGolem::StopAgro()
{
	AIState = EAIState::IDLE;
	MonsterCon->SetAIState(AIState);
}
