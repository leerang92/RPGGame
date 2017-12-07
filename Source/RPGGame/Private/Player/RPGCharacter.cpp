// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraShake.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SkillInformation.h"

ARPGCharacter::ARPGCharacter()
{
	bInputAttack = false;
	bPickupItem = false;
	bPlayAttack = false;
	bIsAttacking = false;

	ViewDistance = 500.0f;
	MaxHP = 100.0f;
	AttackIndex = 1;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ARPGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGCharacter::LookUpAtRate);

	// Active UI
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ARPGCharacter::ActiveInventory);
	InputComponent->BindAction("Skill", IE_Pressed, this, &ARPGCharacter::ActiveSkillUI);

	// Attack
	InputComponent->BindAction("Attack", IE_Pressed, this, &ARPGCharacter::StartAttack);
	InputComponent->BindAction("Attack", IE_Released, this, &ARPGCharacter::StopAttack);

	// PickupItem
	InputComponent->BindAction("Pickup", IE_Pressed, this, &ARPGCharacter::PickupItem);

	// Use Skill
	InputComponent->BindAction("Skill_1", IE_Pressed, this, &ARPGCharacter::UseSkill<0>);
	InputComponent->BindAction("Skill_2", IE_Pressed, this, &ARPGCharacter::UseSkill<1>);
	InputComponent->BindAction("Skill_3", IE_Pressed, this, &ARPGCharacter::UseSkill<2>);
	InputComponent->BindAction("Skill_4", IE_Pressed, this, &ARPGCharacter::UseSkill<3>);
	InputComponent->BindAction("Skill_5", IE_Pressed, this, &ARPGCharacter::UseSkill<4>);
	InputComponent->BindAction("Skill_6", IE_Pressed, this, &ARPGCharacter::UseSkill<5>);
}

void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;

	// Create MainHUD
	UUserWidget* HUD = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);
	HUD->AddToViewport();
	MainHUD = Cast<UMainHUD>(HUD);
	check(MainHUD);
}

void ARPGCharacter::Tick(float DeltaSecondes)
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

void ARPGCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARPGCharacter::MoveForward(float Value)
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

void ARPGCharacter::MoveRight(float Value)
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

float ARPGCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	SetHP(-ActualDamage);

	return ActualDamage;
}

bool ARPGCharacter::IsAttack() const
{
	return CurrentWeapon != nullptr && !bIsAttacking && AttackAnims.Num() > 0;
}

bool ARPGCharacter::IsAttacking() const
{
	return bIsAttacking;
}

void ARPGCharacter::StartAttack()
{
	bInputAttack = true;
	if (IsAttack())
	{
		ComboAttack();
	}
}

void ARPGCharacter::StopAttack()
{
	bInputAttack = false;
	//bPlayAttack = false;
}

void ARPGCharacter::ComboAttack()
{
	bIsAttacking = true;
	if (AttackIndex >= AttackAnims.Num())
	{
		AttackIndex = 0;
	}
	SetAnimation(AttackAnims[AttackIndex]);
	++AttackIndex;
}

void ARPGCharacter::OnDeath()
{
}

float ARPGCharacter::SetAnimation(UAnimMontage * Animation, float InPlayRate, FName StartSelectName)
{
	return PlayAnimMontage(Animation, InPlayRate, StartSelectName);
}

void ARPGCharacter::StopAttackAnim()
{
	bPlayAttack = false;
}

void ARPGCharacter::SetSkill(FSkillInfo Info)
{
	UE_LOG(LogClass, Warning, TEXT("Skill"));
	SetAnimation(Info.SkillAnim);
}

ABaseItem * ARPGCharacter::GetPickupItem() const
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

void ARPGCharacter::PickupItem()
{
	if (bPickupItem)
	{
		CurrentViewItem->OnPickup(this);
	}
}

void ARPGCharacter::AddItem(ABaseItem * Item)
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

void ARPGCharacter::SetHP(float NewHP)
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

void ARPGCharacter::ActiveInventory()
{
	if (MainHUD)
	{
		MainHUD->ActiveInventory();
	}
}

void ARPGCharacter::ActiveSkillUI()
{
	if (MainHUD)
	{
		MainHUD->ActiveSkillUI();
	}
}

template<int Key>
void ARPGCharacter::UseSkill()
{
	MainHUD->GetSkillBar()->OnUsedSkill(Key);
}

void ARPGCharacter::StartCameraShake()
{
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), CamShake, GetActorLocation(), 0.0f, 500.0f);
}

void ARPGCharacter::StartSlowMotion()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), SlowTime);
	FTimerHandle SlowTimer;
	GetWorldTimerManager().SetTimer(SlowTimer, this, &ARPGCharacter::StopSlowMotion, 0.25f, false);
}

void ARPGCharacter::StopSlowMotion()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

