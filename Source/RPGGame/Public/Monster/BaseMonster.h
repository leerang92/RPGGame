// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Types.h"
#include "BaseMonsterController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

UCLASS()
class RPGGAME_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
	class USphereComponent* AgroColl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackDistance;

	UPROPERTY(EditAnywhere, Category = Behavior)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = Animation)
	TArray<UAnimMontage*> AttackAnims;

	UFUNCTION(BlueprintCallable, Category = State)
	FORCEINLINE EAIState GetAIState() const { return AIState; }

	virtual void ComboAttack();

	UPROPERTY(BlueprintReadOnly, Category = Attack)
	int AttackIndex;

	UPROPERTY(BlueprintReadOnly, Category = Attack)
	bool bAttack;

	bool bAttacking;

	bool IsAttack();

	void SetFocus();

	UPROPERTY(EditAnywhere, Category = Rotation)
	float LookSpeed;
protected:
	float HP;

	UPROPERTY()
	APawn* TargetPawn;

	EAIState AIState;

	UPROPERTY()
	class ABaseMonsterController* MonsterCon;

	UFUNCTION()
	virtual void OnAgroOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnMeleeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle WaitTimer;

	float PlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

private:
	float SetOrientation;

	float Angular;

	float UpdateRotation;
};
