// Fill out your copyright notice in the Description page of Project Settings.

#include "PChacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "SkillInformation.h"

//////////////////////////////////////////////////////////////////////////
// ARPGGameCharacter

APCharacter::APCharacter()
{
	bInputAttack = false;
	bPickupItem = false;
	bPlayAttack = false;

	ViewDistance = 500.0f;
	MaxHP = 100.0f;
	AttackIndex = 1;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; 
}

void APCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APCharacter::LookUpAtRate);

	// Active UI
	InputComponent->BindAction("Inventory", IE_Pressed, this, &APCharacter::ActiveInventory);
	InputComponent->BindAction("Skill", IE_Pressed, this, &APCharacter::ActiveSkillUI);

	// Attack
	InputComponent->BindAction("Attack", IE_Pressed, this, &APCharacter::StartAttack);
	InputComponent->BindAction("Attack", IE_Released, this, &APCharacter::StopAttack);

	// PickupItem
	InputComponent->BindAction("Pickup", IE_Pressed, this, &APCharacter::PickupItem);

	// Use Skill
	InputComponent->BindAction("Skill_1", IE_Pressed, this, &APCharacter::UseSkill<0>);
	InputComponent->BindAction("Skill_2", IE_Pressed, this, &APCharacter::UseSkill<1>);
	InputComponent->BindAction("Skill_3", IE_Pressed, this, &APCharacter::UseSkill<2>);
	InputComponent->BindAction("Skill_4", IE_Pressed, this, &APCharacter::UseSkill<3>);
	InputComponent->BindAction("Skill_5", IE_Pressed, this, &APCharacter::UseSkill<4>);
	InputComponent->BindAction("Skill_6", IE_Pressed, this, &APCharacter::UseSkill<5>);
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;

	// Create MainHUD
	UUserWidget* HUD = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);
	HUD->AddToViewport();
	MainHUD = Cast<UMainHUD>(HUD);
	check(MainHUD);
}

void APCharacter::Tick(float DeltaSecondes)
{
	Super::Tick(DeltaSecondes);

	//// 카메라가 봐라보는 아이템
	ABaseItem* FocusItem = GetPickupItem();

	if (CurrentViewItem != FocusItem)
	{
		if (CurrentViewItem)
		{
			CurrentViewItem->EndFouceItem();
			MainHUD->ActiveGetUI(false);
		}
		bPickupItem = false;
	}

	CurrentViewItem = FocusItem;

	if (CurrentViewItem != nullptr)
	{
		CurrentViewItem->OnFouceItem();
		MainHUD->ActiveGetUI(true);
		bPickupItem = true;
	}

}

void APCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

float APCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	SetHP(-ActualDamage);

	return ActualDamage;
}

bool APCharacter::IsAttack() const
{
	return CurrentWeapon != nullptr && AttackAnims.Num() > 0;
}

bool APCharacter::IsAttacking() const
{
	return bPlayAttack;
}

void APCharacter::StartAttack()
{
	if (IsAttack() && !IsAttacking() && !bInputAttack)
	{
		AttackIndex = 0;
		SetAnimation(AttackAnims[AttackIndex]);
		bPlayAttack = true;
		bInputAttack = true;
	}
}

void APCharacter::StopAttack()
{
	bInputAttack = false;
	//bPlayAttack = false;
}

void APCharacter::OnDeath()
{
}

float APCharacter::SetAnimation(UAnimMontage * Animation, float InPlayRate, FName StartSelectName)
{
	return PlayAnimMontage(Animation, InPlayRate, StartSelectName);
}

void APCharacter::StopAttackAnim()
{
	bPlayAttack = false;
}

void APCharacter::ComboAttack()
{
	++AttackIndex;
	if (AttackIndex >= AttackAnims.Num())
	{
		AttackIndex = 0;
	}
	SetAnimation(AttackAnims[AttackIndex]);
}

void APCharacter::SetSkill(FSkillInfo Info)
{
	SetAnimation(Info.SkillAnim);
}

ABaseItem * APCharacter::GetPickupItem() const
{
	if (Controller == nullptr)
		return nullptr;

	/* 카메라에서 ViewDistance까지 트레이스 발사 */
	FVector CameraVec = FVector::ZeroVector;
	FRotator CameraRot = FRotator::ZeroRotator;
	Controller->GetPlayerViewPoint(CameraVec, CameraRot);

	const FVector Direction = CameraRot.Vector();
	const FVector Distance = CameraVec + (Direction * ViewDistance);

	/* 트레이스 발사 */
	FCollisionQueryParams TraceParam(TEXT("Item Trace"), true, this);
	TraceParam.bTraceAsyncScene = true;
	TraceParam.bReturnPhysicalMaterial = false;
	TraceParam.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, CameraVec, Distance, ECC_Visibility, TraceParam);

	return Cast<ABaseItem>(Hit.GetActor());
}

void APCharacter::PickupItem()
{
	if (bPickupItem)
	{
		CurrentViewItem->OnPickup(this);
	}
}

void APCharacter::AddItem(ABaseItem * Item)
{
	if (Item != nullptr)
	{
		if (CurrentWeapon == nullptr && Item->Info.Type == EItemType::WEAPON)
		{
			CurrentWeapon = Item;
			CurrentWeapon->OnUsed(this);
		}
		else
		{
			ItemArr.Add(Item);
			MainHUD->GetInventory()->AddItem(Item->Info);
			Item->SetLifeSpan(0.001f);
		}
	}
}

void APCharacter::SetHP(float NewHP)
{
	HP = FMath::Min((HP + NewHP), MaxHP);
	if (MainHUD != nullptr && MainHUD->GetPlayerState() != nullptr)
	{
		MainHUD->GetPlayerState()->SetHP(HP);
	}

	if (HP <= 0.0f)
	{
		OnDeath();
	}
}

void APCharacter::ActiveInventory()
{
	if (MainHUD)
	{
		MainHUD->ActiveInventory();
	}
}

void APCharacter::ActiveSkillUI()
{
	if (MainHUD)
	{
		MainHUD->ActiveSkillUI();
	}
}

template<int Key>
void APCharacter::UseSkill()
{
	MainHUD->GetSkillBar()->OnUsedSkill(Key);
}



