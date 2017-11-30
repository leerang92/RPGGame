// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "RPGGameCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ARPGGameCharacter

ARPGGameCharacter::ARPGGameCharacter()
{
	bWeapon = false;
	bAttack = false;
	bPickupItem = false;

	ViewDistance = 500.0f;

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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARPGGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPGGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGGameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARPGGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARPGGameCharacter::TouchStopped);

	// Active UI
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ARPGGameCharacter::ActiveInventory);

	// Attack
	InputComponent->BindAction("Attack", IE_Pressed, this, &ARPGGameCharacter::StartAttack);
	InputComponent->BindAction("Attack", IE_Released, this, &ARPGGameCharacter::StopAttack);

	// PickupItem
	InputComponent->BindAction("Pickup", IE_Pressed, this, &ARPGGameCharacter::PickupItem);
}

void ARPGGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Create MainHUD
	UUserWidget* HUD = CreateWidget<UUserWidget>(GetWorld(), MainHUDClass);
	HUD->AddToViewport();
	MainHUD = Cast<UMainHUD>(HUD);
	check(MainHUD);
}

void ARPGGameCharacter::Tick(float DeltaSecondes)
{
	Super::Tick(DeltaSecondes);

	//// 카메라가 봐라보는 아이템
	ABaseItem* FocusItem = GetPickupItem();

	if (CurrentViewItem != FocusItem)
	{
		if (CurrentViewItem)
		{
			CurrentViewItem->EndFouceItem();
		}
		bPickupItem = false;
	}

	CurrentViewItem = FocusItem;

	if (CurrentViewItem != nullptr)
	{
		CurrentViewItem->OnFouceItem();
		bPickupItem = true;
	}

}

void ARPGGameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ARPGGameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ARPGGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARPGGameCharacter::MoveForward(float Value)
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

void ARPGGameCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
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

bool ARPGGameCharacter::IsAttack() const
{
	return bWeapon;
}

bool ARPGGameCharacter::IsAttacking() const
{
	return bAttack;
}


void ARPGGameCharacter::StartAttack()
{
	if (IsAttack())
	{
		bAttack = true;
	}
}

void ARPGGameCharacter::StopAttack()
{
	bAttack = false;
}

ABaseItem * ARPGGameCharacter::GetPickupItem() const
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

void ARPGGameCharacter::PickupItem()
{
	if (bPickupItem)
	{
		CurrentViewItem->OnPickup(this);
		bWeapon = true;
	}
}

void ARPGGameCharacter::AddItem(ABaseItem * Item)
{
	if (Item != nullptr)
	{
		if (CurrentWeapon == nullptr)
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

void ARPGGameCharacter::ActiveInventory()
{
	if (MainHUD)
	{
		MainHUD->ActiveInventory();
	}
}

