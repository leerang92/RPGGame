// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Types.h"
#include "RPGGameCharacter.h"
#include "UserWidget.h"
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

	/* Attack */
	UPROPERTY(EditAnywhere, Category = Animation)
	TArray<UAnimMontage*> AttackAnims;

	virtual void ComboAttack();

	UPROPERTY(BlueprintReadOnly, Category = Attack)
	int AttackIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDistance;

	UPROPERTY(BlueprintReadOnly, Category = Attack)
	bool bAttack;

	bool bAttacking;

	bool IsAttack();

	void SetFocus();

	// 포커스 속도
	UPROPERTY(EditAnywhere, Category = Rotation)
	float LookSpeed;

	UFUNCTION(BlueprintCallable, Category = Health)
	FORCEINLINE bool IsAlive() const { return HP > 0.0f; }

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> DamageWidgetClass;

protected:
	float HP;

	UPROPERTY()
	APawn* TargetPawn;

	EAIState AIState;

	UPROPERTY()
	class ABaseMonsterController* MonsterCon;

	FTimerHandle WaitTimer;

	UFUNCTION()
	virtual void OnAgroOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnMeleeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float PlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	void OnDeath();

	void CreateDamageWidget(float Damage);

private:
	/* 포커스 변수들 */
	float SetOrientation;

	float Angular;

	float UpdateRotation;
};
