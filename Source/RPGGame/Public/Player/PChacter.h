// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "MainHUD.h"
#include "BaseItem.h"
#include "GameFramework/Character.h"
#include "PChacter.generated.h"

UCLASS()
class RPGGAME_API APCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecondes) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		TArray<UAnimMontage*> AttackAnims;

	void ComboAttack();

	bool bInputAttack;

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
