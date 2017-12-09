// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonster.h"
#include "UIDamage.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAttacking = false;
	bIsSetAttack = false;
	bIsCritical = false;

	MaxHP = 100.0f;
	HP = MaxHP;

	AttackIndex = 0;
	AttackDistance = 200.0f;

	LookSpeed = 200.0f;
	SetOrientation = 100.0f;
	Angular = 0.0f;
	UpdateRotation = 0.0;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Comp"));
	PawnSensing->SetPeripheralVisionAngle(60.0f);
	PawnSensing->SightRadius = 3000.0f;
	PawnSensing->HearingThreshold = 10.0f;
	PawnSensing->OnSeePawn.AddDynamic(this, &ABaseMonster::OnSeePlayer);
	PawnSensing->OnHearNoise.AddDynamic(this, &ABaseMonster::OnHearingPlayer);

	AttackColl = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Attack Collider"));
	AttackColl->AttachTo(GetCapsuleComponent());
	AttackColl->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapBegin);
	AttackColl->OnComponentEndOverlap.AddDynamic(this, &ABaseMonster::OnAttackOverlapEnd);

	AIState = EAIState::IDLE;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;

	if (GetController())
	{
		MonsterCon = Cast<ABaseMonsterController>(GetController());
		check(MonsterCon);
		MonsterCon->HomeLocation = GetActorLocation();
		MonsterCon->SetAIState(AIState);
	}
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABaseMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (IsAlive())
	{
		//float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
		HP -= Damage;
		HP = FMath::Max(HP, 0.0f);

		CreateDamageWidget(Damage);

		if (HP <= 0.0f)
		{
			OnDeath();
		}
	}
	return Damage;
}

void ABaseMonster::CreateDamageWidget(float Damage)
{
	if (DamageWidgetClass != nullptr)
	{
		UUserWidget* DamageWidget = CreateWidget<UUserWidget>(GetWorld(), DamageWidgetClass);
		DamageWidget->AddToViewport();
		UUIDamage* DamageUI = Cast<UUIDamage>(DamageWidget);
		if (DamageUI)
		{
			DamageUI->SetDamage(Damage, GetActorLocation(), bIsCritical);
		}
	}
}

void ABaseMonster::OnSeePlayer(APawn* Pawn)
{
	ARPGCharacter* PC = Cast<ARPGCharacter>(Pawn);
	if (PC && !IsAttack() && !bAttacking)
	{
		MonsterCon->SetAIState(EAIState::MOVE);
		MonsterCon->SetTargetPawn(Pawn);
	}
}

void ABaseMonster::OnHearingPlayer(APawn* Pawn, const FVector& Location, float Volume)
{
	UE_LOG(LogClass, Warning, TEXT("Hearing"));
	ARPGCharacter* PC = Cast<ARPGCharacter>(Pawn);
	if (PC && !IsAttack() && !bAttacking)
	{
		MonsterCon->SetAIState(EAIState::MOVE);
		MonsterCon->SetTargetPawn(Pawn);
	}
}

void ABaseMonster::SetRandomLocation()
{
	GetWorldTimerManager().ClearTimer(WanderTimer);

	float RandX = FMath::RandRange(-1000.0f, 1000.0f);
	float RandY = FMath::RandRange(-1000.0f, 1000.0f);

	FVector MoveLocation = MonsterCon->HomeLocation + FVector(RandX, RandY, 0);

	MonsterCon->SetMoveLocation(MoveLocation);

	GetWorldTimerManager().SetTimer(WanderTimer, this, &ABaseMonster::SetRandomLocation, 3.0f, true);
}

void ABaseMonster::ItemDrop()
{
	const FVector ActorLoc = GetActorLocation();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.Instigator = Instigator;

	for (int i = 0; i < DropItemArr.Num(); ++i)
	{
		ABaseItem* Item = Cast<ABaseItem>(DropItemArr[i]->ClassDefaultObject);
		if (Item)
		{
			if (Item->Info.IsDropItem())
			{
				/* 액터 기준으로 X, Y의 랜덤한 위치에 스폰 */
				const float rX = FMath::RandRange(-200.0f, 200.0f);
				const float rY = FMath::RandRange(-200.0f, 200.0f);
				const FVector SpawnLoc = ActorLoc + FVector(rX, rY, 0.0f);
				
				GetWorld()->SpawnActor<AActor>(DropItemArr[i], SpawnLoc, FRotator::ZeroRotator, SpawnInfo);
			}
		}
	}

	
}

void ABaseMonster::OnMeleeOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void ABaseMonster::OnAttackOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

bool ABaseMonster::IsAttack()
{
	return bIsSetAttack;

	// 캐릭터와의 각도를 구함 (0 ~ 1 사이)
	/*const FVector ForwardVec = GetActorForwardVector();
	FVector TargetOffset = TargetPawn->GetActorLocation() - GetActorLocation();
	TargetOffset = TargetOffset.GetSafeNormal();
	float Angle = FVector::DotProduct(ForwardVec, TargetOffset);
	float Dist = FVector::Distance(GetActorLocation(), TargetPawn->GetActorLocation());

	if (Angle >= 0.91f && Dist <= AttackDistance) 
	{ 
		return true; 
	}

	return false;*/
}

void ABaseMonster::ComboAttack()
{
	bAttacking = true;
	if (AttackIndex >= AttackAnims.Num())
	{
		AttackIndex = 0;
	}
	PlayAnimation(AttackAnims[AttackIndex]);
	++AttackIndex;
}

void ABaseMonster::OnAttackOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

float ABaseMonster::PlayAnimation(UAnimMontage * Animation, float InPlayRate, FName StartSelectName)
{
	return PlayAnimMontage(Animation, InPlayRate, StartSelectName);
}

void ABaseMonster::OnDeath()
{
	// 애니메이션 중지
	StopAnimMontage(AttackAnims[0]);

	// Controller 해제
	DetachFromControllerPendingDestroy();

	/* Collider 무시 */
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	// 아이템 드랍
	ItemDrop();
}

void ABaseMonster::SetFocus()
{
	if (MonsterCon->GetTargetPawn() == nullptr)
		return;

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector Direction = MonsterCon->GetTargetPawn()->GetActorLocation() - GetActorLocation();
	float Orientation = FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
	
	float Rotation = Orientation - SetOrientation;
	Rotation = FMath::Fmod(Rotation, 360.0f);
	if (FMath::Abs(Rotation) > 180.0f)
	{
		if (Rotation < 0.0f)
			Rotation += 360.0f;
		else
			Rotation -= 360.0f;
	}

	float RotationSize = FMath::Abs(Rotation);
	float TargetRotation = LookSpeed * (Rotation / RotationSize);
	Angular = TargetRotation - UpdateRotation;
	Angular /= 0.1f;

	UpdateRotation += Angular * DeltaTime;
	if (UpdateRotation > 45.0f)
		UpdateRotation = 45.0f;
	if (Angular == 0.0f)
		Angular = 0.0f;
		
	SetOrientation += UpdateRotation * DeltaTime;
	if (SetOrientation < 0.0f)
	{
		SetOrientation += 360.0f;
	}
	else if (SetOrientation > 360.0f)
	{
		SetOrientation -= 360.0f;
	}

	FRotator MoveRototation = GetActorRotation();
	MoveRototation.Yaw = SetOrientation;
	SetActorRotation(MoveRototation);
}

