// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipItem.h"
#include "RPGGameCharacter.h"
#include "BaseMonster.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AEquipItem::AEquipItem()
{
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	//CapsuleComp->Attachment(MeshComp);
	CapsuleComp->AttachTo(MeshComp);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AEquipItem::OnOverlapBegin);
}

void AEquipItem::OnPickup(APawn* Owner)
{
	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);
	check(PC);
	OwnerPawn = Owner;

	//Super::OnPickup(Owner);
	PC->AddItem(this);
}

void AEquipItem::OnUsed(APawn* Owner)
{
	ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(Owner);
	check(PC);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FName AttachPoint = TEXT("hand_rWeaponSocket");
	MeshComp->AttachToComponent(PC->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
}

void AEquipItem::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		AActor* Monster = Cast<ABaseMonster>(OtherActor);
		if (Monster)
		{
			// 캐릭터가 공격 애니메이션중이면 데미지 전달
			ARPGGameCharacter* PC = Cast<ARPGGameCharacter>(OwnerPawn);
			if (PC && PC->IsAttacking())
			{
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				FDamageEvent DamageEvent(ValidDamageTypeClass);
				Monster->TakeDamage(10.0f, DamageEvent, nullptr, nullptr);

				PlayParticle(AttackFX, OtherActor->GetActorLocation());
			}
		}
	}
}


UParticleSystemComponent * AEquipItem::PlayParticle(UParticleSystem * NewFX, FVector SpawnLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NewFX, SpawnLocation);
	return nullptr;
}
