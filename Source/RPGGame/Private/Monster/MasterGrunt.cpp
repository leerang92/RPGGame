// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterGrunt.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "UIDamage.h"

AMasterGrunt::AMasterGrunt()
{
	bInTarget = false;
	bAttack = false;
	bAttacking = false;

	RWeaponSocketName = TEXT("b_MF_Weapon_R");
	LWeaponSocketName = TEXT("b_MF_Weapon_L");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Weapon(TEXT("StaticMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/SM_Master_Grunt_Blade_Internal.SM_Master_Grunt_Blade_Internal'"));
	RWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Weapon Mesh"));
	RWeaponMesh->SetStaticMesh(SM_Weapon.Object);
	RWeaponMesh->AttachTo(GetMesh(), RWeaponSocketName);

	LWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Weapon Mesh"));
	LWeaponMesh->SetStaticMesh(SM_Weapon.Object);
	LWeaponMesh->AttachTo(GetMesh(), LWeaponSocketName);

	RWeaponColl = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Right Weapon Collider"));
	RWeaponColl->AttachTo(RWeaponMesh);
	RWeaponColl->OnComponentBeginOverlap.AddDynamic(this, &AMasterGrunt::OnMeleeOverlapBegin);

	LWeaponColl = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Left Weapon Collider"));
	LWeaponColl->AttachTo(LWeaponMesh);
	LWeaponColl->OnComponentBeginOverlap.AddDynamic(this, &AMasterGrunt::OnMeleeOverlapBegin);
}

void AMasterGrunt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTarget())
	{
		if (IsAttack() && !bAttack)
		{
			MonsterCon->SetAIState(EAIState::ATTACK);
			ComboAttack();
		}
		else if(!IsAttack() && !bAttacking)
		{
			MonsterCon->SetAIState(EAIState::MOVE);
			//SetFocus();
		}
	}
}

void AMasterGrunt::OnAgroOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(OtherActor);
		if (PC)
		{
			bInTarget = true;
			TargetPawn = PC;
			MonsterCon->SetTargetPawn(TargetPawn);
			MonsterCon->SetAIState(EAIState::MOVE);
		}
	}
}

void AMasterGrunt::OnMeleeOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(OtherActor);
		if (PC && bAttacking)
		{
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent DamageEvent(ValidDamageTypeClass);
			PC->TakeDamage(10.0f, DamageEvent, MonsterCon, nullptr);
		}
	}
}

void AMasterGrunt::ComboAttack()
{
	Super::ComboAttack();
}


void AMasterGrunt::StopAgro()
{
}
