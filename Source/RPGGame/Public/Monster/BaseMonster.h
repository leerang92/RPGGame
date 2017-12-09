// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Types.h"
#include "RPGCharacter.h"
#include "UserWidget.h"
#include "BaseItem.h"
#include "BaseMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

UCLASS()
class RPGGAME_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:	
	ABaseMonster();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// 데미지 받는 함수
	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	UPROPERTY(EditAnywhere, Category = Behavior)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	float MaxHP;

	/* Target Focus */
	UPROPERTY(EditAnywhere, Category = Rotation)
	float LookSpeed;

	void SetFocus();

	// 생존 여부
	UFUNCTION(BlueprintCallable, Category = Health)
	FORCEINLINE bool IsAlive() const { return HP > 0.0f; }

	/* 딜량 UI */
	// 딜량 표시 UI 클래스
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> DamageWidgetClass;

	// 크리티컬 데미지 받은 여부
	bool bIsCritical;

	/* Pawn Sensing */
	UPROPERTY(EditAnywhere, Category = AI)
	UPawnSensingComponent* PawnSensing;

protected:
	float HP;

	// 몬스터 컨트롤러
	UPROPERTY()
	class ABaseMonsterController* MonsterCon;

	EAIState AIState;

	FTimerHandle WaitTimer;

	// 몽타주 애니메이션 재생
	float PlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	// 받은 데미지 표시 UI 생성
	void CreateDamageWidget(float Damage);

	UFUNCTION()
	virtual void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
	void OnHearingPlayer(APawn* Pawn, const FVector& Location, float Volume);

	FTimerHandle WanderTimer;

	void SetRandomLocation();

public:
	/* Attack */
	UPROPERTY(EditAnywhere, Category = Collider)
	UCapsuleComponent* AttackColl;

	UPROPERTY(EditAnywhere, Category = Animation)
	TArray<UAnimMontage*> AttackAnims;

	// 연속 공격 함수
	virtual void ComboAttack();

	// 현재 공격 애니메이션 인덱스
	UPROPERTY(BlueprintReadOnly, Category = Attack)
	int AttackIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDistance;

	// 현재 공격 중인 여부
	bool bAttacking;

	// 공격 가능 여부
	bool bIsSetAttack;

	// 공격 가능 여부 반환 함수
	bool IsAttack();

private:
	/* 포커스 변수들 */
	float SetOrientation;

	float Angular;

	float UpdateRotation;

protected:
	/* Drop Item */
	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABaseItem>> DropItemArr;

	void ItemDrop();

	/* 사망 */
	void OnDeath();

	void RemoveActor();

	FTimerHandle RemoveTimer;

	UPROPERTY(EditAnywhere, Category = Death, meta = (AllowPrivateAccess = "ture"))
	float RemoveTime;

protected:
	/* 충돌 처리 */
	UFUNCTION()
	virtual void OnMeleeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
