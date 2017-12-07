// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "MainHUD.h"
#include "BaseItem.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS()
class RPGGAME_API ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGCharacter();

	/* Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, Category = Camera)
	TSubclassOf<UCameraShake> CamShake;

	void StartCameraShake();

	UPROPERTY(EditAnywhere, Category = Camera)
	float SlowTime;

	void StartSlowMotion();

	void StopSlowMotion();

protected:
	/* Movement */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecondes) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UUserWidget> MainHUDClass;

	/* Health */
	void SetHP(float NewHP);

	FORCEINLINE float GetMaxHP() const { return MaxHP; }

	FORCEINLINE UMainHUD* GetMainHUD() const { return MainHUD; }

	// ���� �������� �迭�� �߰�
	void AddItem(ABaseItem* Item);

	/* �ִϸ��̼� */
	float SetAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	void StopAttackAnim();

public:
	/* ���� */
	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsAttack() const;

	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsAttacking() const;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	FORCEINLINE bool IsWeapon() const { return CurrentWeapon != nullptr; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TArray<UAnimMontage*> AttackAnims;

	void ComboAttack();

	bool bInputAttack;

	bool bIsAttacking;

	void SetSkill(FSkillInfo Info);
private:
	/* UI */
	UPROPERTY()
	class UMainHUD* MainHUD;

	void ActiveInventory();

	void ActiveSkillUI();

	/* Attack */
	int AttackIndex;

	bool bPlayAttack;

	void StartAttack();

	void StopAttack();

	/* Character State */
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	float MaxHP;

	/* Skill */
	template<int Key>
	void UseSkill();

	void OnDeath();

private:
	/* Item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = View, meta = (AllowPrivateAccess = "true"))
		float ViewDistance;

	// ���� ������ ���� Ŭ����
	class ABaseItem* CurrentWeapon;

	// ������ �ݱ� ���� ����
	bool bPickupItem;

	// ���� ���� �ִ� ������ Ŭ����
	UPROPERTY()
	class ABaseItem* CurrentViewItem;

	// ������ �ִ� ������ �迭
	TArray<class ABaseItem*> ItemArr;

	// �ݱ� ������ ������ ��ȯ �Լ�
	ABaseItem* GetPickupItem() const;

	// ������ �ݱ� �Լ�
	void PickupItem();
};
