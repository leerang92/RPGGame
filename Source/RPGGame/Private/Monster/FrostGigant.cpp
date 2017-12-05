// Fill out your copyright notice in the Description page of Project Settings.

#include "FrostGigant.h"
#include "RPGGameCharacter.h"


void AFrostGigant::BeginPlay()
{
	Super::BeginPlay();

	bAttack = false;
	bAttacking = false;
}

void AFrostGigant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIState == EAIState::ATTACK)
	{
		if (!IsAttack() && !bAttacking)
		{
			SetFocus();
		}
		else if(IsAttack() && !bAttack)
		{
			UE_LOG(LogClass, Warning, TEXT("Check"));
			ComboAttack();
		}
	}
}

void AFrostGigant::OnAgroOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnAgroOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(OtherActor);
		if (PC)
		{
			AIState = EAIState::AGRO;
			//MonsterCon->SetTargetPawn(PC);
			GetWorldTimerManager().SetTimer(WaitTimer, this, &AFrostGigant::SetAttack, 2.876f, false);
		}
	}
}

void AFrostGigant::SetAttack()
{
	AIState = EAIState::ATTACK;
	MonsterCon->SetAIState(AIState);

	AttackIndex = 0;
	//ComboAttack();
}

void AFrostGigant::ComboAttack()
{
	bAttack = true;
	if (AttackIndex >= AttackAnims.Num())
	{
		AttackIndex = 0;
	}
	PlayAnimation(AttackAnims[AttackIndex]);
	++AttackIndex;
}

