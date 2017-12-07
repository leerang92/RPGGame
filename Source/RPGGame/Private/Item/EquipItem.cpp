// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipItem.h"
#include "RPGCharacter.h"
#include "BaseMonster.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AEquipItem::AEquipItem()
{
	/* 무기 컬리더 */
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComp->AttachTo(MeshComp);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AEquipItem::OnOverlapBegin);
}

void AEquipItem::OnPickup(APawn* Owner)
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);
	check(PC);
	OwnerPawn = Owner;

	PC->AddItem(this);
}

void AEquipItem::OnUsed(APawn* Owner)
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);
	check(PC);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/* 무기를 오른쪽 무기 소켓에 부착 */
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
			UE_LOG(LogClass, Warning, TEXT("Set!!!"));
			// 캐릭터가 공격 애니메이션중이면 데미지 전달
			ARPGCharacter* PC = Cast<ARPGCharacter>(OwnerPawn);
			if (PC && PC->IsAttacking())
			{
				// 무기내 데미지 범위 내 전달할 데미지 산정
				const float ActualDamage = FMath::RandRange(MinDamage, MaxDamage);

				/* 데미지 전달*/
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				FDamageEvent DamageEvent(ValidDamageTypeClass);
				Monster->TakeDamage(ActualDamage, DamageEvent, nullptr, nullptr);

				/* Effect 생성 */
				AEffectActor* Effect = GetWorld()->SpawnActorDeferred<AEffectActor>(EffectClass, OtherActor->GetActorLocation(), FRotator::ZeroRotator);
				if (Effect)
				{
					Effect->Type = EEffectType::BLOOD;
					UGameplayStatics::FinishSpawningActor(Effect, FTransform(FRotator::ZeroRotator, OtherActor->GetActorLocation()));
				}
				PC->StartCameraShake();
			}
		}
	}
}

UParticleSystemComponent * AEquipItem::PlayParticle(UParticleSystem * NewFX, FVector SpawnLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NewFX, SpawnLocation);
	return nullptr;
}
