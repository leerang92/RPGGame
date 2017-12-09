// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "MainHUD.h"
#include "BaseItem.h"
#include "WeaponItem.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS()
class RPGGAME_API ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPGCharacter();

	/* 카메라 */
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

	/* 슬로우 모션 */
	UPROPERTY(EditAnywhere, Category = Camera)
	float SlowTime;

	void StartSlowMotion();

	void StopSlowMotion();

protected:
	/* 이동 함수들 */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecondes) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	/* 키 입력 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// 메인 UI 클래스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UUserWidget> MainHUDClass;

	/* Health */
	void SetHP(float NewHP);

	FORCEINLINE float GetMaxHP() const { return MaxHP; }

	FORCEINLINE UMainHUD* GetMainHUD() const { return MainHUD; }

	// 습득 아이템을 배열에 추가
	void AddItem(ABaseItem* Item);

	/* 애니메이션 */
	float SetAnimation(UAnimMontage* Animation, float InPlayRate = 1.0f, FName StartSelectName = NAME_None);

	void StopAttackAnim();

public:
	/* 공격 */
	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	// 공격 여부 반환
	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsAttack() const;

	// 현재 공격중인지 여부
	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsAttacking() const;

	// 공격 애니메이션 몽타주 배열
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TArray<UAnimMontage*> AttackAnims;

	// 연속 공격
	void ComboAttack();

	// 공격 키 입력 여부
	bool bInputAttack;

	// 현재 공격중인지 여부
	bool bIsAttacking;

	// 스킬 사용
	void SetSkill(FSkillInfo Info);

	// 무기를 가지고 있는지 여부
	UFUNCTION(BlueprintCallable, Category = Weapon)
	FORCEINLINE bool IsWeapon() const { return CurrentWeapon != nullptr; }

	// 무기 교체
	void SwapWeapon(TSubclassOf<ABaseItem> Item);

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

	/* 체력 */
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	float MaxHP;

	// 키 입력에 따른 스킬 호출
	template<int Key>
	void UseSkill();

	/* 사망 */
	void OnDeath();

private:
	/* Item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = View, meta = (AllowPrivateAccess = "true"))
	float ViewDistance;

	// 아이템 줍기 가능 여부
	bool bPickupItem;

	// 현재 장착한 무기 클래스
	class AWeaponItem* CurrentWeapon;

	// 현재 보고 있는 아이템 클래스
	UPROPERTY()
	class ABaseItem* CurrentViewItem;

	// 가지고 있는 아이템 배열
	TArray<class ABaseItem*> ItemArr;

	// 줍기 가능한 아이템 반환 함수
	ABaseItem* GetPickupItem() const;

	// 아이템 줍기 함수
	void PickupItem();
};
