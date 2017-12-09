// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponItem.h"
#include "RPGCharacter.h"
#include "BaseMonster.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AWeaponItem::AWeaponItem()
{
	/* 무기 콜리더 컴포넌트 설정 */
	WeaponColl = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Attack Collider Component"));
	WeaponColl->AttachTo(MeshComp);
	WeaponColl->OnComponentBeginOverlap.AddDynamic(this, &AWeaponItem::OnOverlapBegin);

	// 부착할 소켓의 이름
	AttachPoint = TEXT("hand_rWeaponSocket");
}

void AWeaponItem::OnPickup(APawn * Owner)
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);
	if (PC)
	{
		PC->AddItem(this);
	}
}

void AWeaponItem::OnUsed(APawn * Owner)
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(Owner);
	if (PC && !PC->IsWeapon()) // 무기를 소지하고 있지 않을 때
	{
		OwnerPawn = Owner;
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		/* 무기를 오른쪽 무기 소켓에 부착 */
		MeshComp->AttachToComponent(PC->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachPoint);
	}
	else // 이미 무기를 소지하고 있을 때
	{
		PC->SwapWeapon(Info.ItemClass);
	}
}

void AWeaponItem::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{	
		// 몬스터에게만 데미지 전달
		ABaseMonster* Monster = Cast<ABaseMonster>(OtherActor);
		if (Monster)
		{
			// 캐릭터가 공격 애니메이션중이면 데미지 전달
			ARPGCharacter* PC = Cast<ARPGCharacter>(OwnerPawn);
			if (PC && PC->IsAttacking() && IsTakeDamage(*OtherActor))
			{
				/* 데미지 전달 */
				const float ActualDamage = WeaponInfo.GetDamage();
				Monster->bIsCritical = WeaponInfo.IsCritical();
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				FDamageEvent DamageEvent(ValidDamageTypeClass);
				OtherActor->TakeDamage(ActualDamage, DamageEvent, nullptr, nullptr);
				
				/* Effect 생성 */
				AEffectActor* Effect = GetWorld()->SpawnActorDeferred<AEffectActor>(EffectClass, OtherActor->GetActorLocation(), FRotator::ZeroRotator);
				if (Effect)
				{
					Effect->Type = EEffectType::BLOOD;
					UGameplayStatics::FinishSpawningActor(Effect, FTransform(FRotator::ZeroRotator, OtherActor->GetActorLocation()));
				}
				// 카메라 흔들기
				PC->StartCameraShake();
				// 사운드 재생
				PlaySound(WeaponInfo.Sound);
				// 데미지를 준 액터 추가
				TakeDamageActors.Add(OtherActor);
			}
		}
	}
}

bool AWeaponItem::IsTakeDamage(AActor& GetActor) const
{
	return TakeDamageActors.Find(&GetActor);
}

void AWeaponItem::SetResetActorArray()
{
	TakeDamageActors.Reset(0);
}

void AWeaponItem::PlaySound(USoundCue * Sound)
{
	if (Sound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Sound, GetActorLocation(), FRotator::ZeroRotator);
	}
}
