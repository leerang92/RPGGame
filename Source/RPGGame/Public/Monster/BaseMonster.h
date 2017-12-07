// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
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

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* AgroColl;

	UPROPERTY(EditAnywhere, Category = Behavior)
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable, Category = State)
	FORCEINLINE EAIState GetAIState() const { return AIState; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	float MaxHP;

	/* Target Focus */
	UPROPERTY(EditAnywhere, Category = Rotation)
	float LookSpeed;

	void SetFocus();

	// ���� ����
	UFUNCTION(BlueprintCallable, Category = Health)
	FORCEINLINE bool IsAlive() const { return HP > 0.0f; }

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> DamageWidgetClass;

protected:
	float HP;

	UPROPERTY()
	class ABaseMonsterController* MonsterCon;

	UPROPERTY()
	APawn* TargetPawn;

	EAIState AIState;

	FTimerHandle WaitTimer;

	// ��Ÿ�� �ִϸ��̼� ���
	float PlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	// ���� ������ ǥ�� UI ����
	void CreateDamageWidget(float Damage);

public:
	/* Attack */
	UPROPERTY(EditAnywhere, Category = Collider)
	UCapsuleComponent* AttackColl;

	UPROPERTY(EditAnywhere, Category = Animation)
	TArray<UAnimMontage*> AttackAnims;

	virtual void ComboAttack();

	UPROPERTY(BlueprintReadOnly, Category = Attack)
	int AttackIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDistance;

	bool bAttacking;

	bool bIsSetAttack;

	bool IsAttack();

private:
	/* ��Ŀ�� ������ */
	float SetOrientation;

	float Angular;

	float UpdateRotation;

protected:
	/* Drop Item */
	UPROPERTY(EditAnywhere, Category = Item, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABaseItem>> DropItemArr;

	void ItemDrop();

	void OnDeath();

protected:
	/* �浹 ó�� */
	UFUNCTION()
	virtual void OnAgroOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnMeleeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
