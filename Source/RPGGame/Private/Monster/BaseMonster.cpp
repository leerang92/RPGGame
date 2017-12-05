// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMonster.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "RPGGameCharacter.h"

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAttacking = false;

	AttackIndex = 0;
	AttackDistance = 200.0f;

	LookSpeed = 200.0f;
	SetOrientation = 100.0f;
	Angular = 0.0f;
	UpdateRotation = 0.0;

	AgroColl = CreateDefaultSubobject<USphereComponent>(TEXT("Agro Collsion Component"));
	AgroColl->AttachTo(GetCapsuleComponent());
	AgroColl->OnComponentBeginOverlap.AddDynamic(this, &ABaseMonster::OnAgroOverlapBegin);

	AIState = EAIState::IDLE;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
	MonsterCon = Cast<ABaseMonsterController>(GetController());
	check(MonsterCon);
	MonsterCon->SetAIState(AIState);

}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABaseMonster::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogClass, Warning, TEXT("Take Damage : %f"), ActualDamage);
	return ActualDamage;
}

void ABaseMonster::OnAgroOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}

void ABaseMonster::OnMeleeOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

bool ABaseMonster::IsAttack()
{
	//float Dir = GetDotProductTo(Character);
	// 캐릭터와의 각도를 구함 (0 ~ 1 사이)
	const FVector ForwardVec = GetActorForwardVector();
	FVector TargetOffset = TargetPawn->GetActorLocation() - GetActorLocation();
	TargetOffset = TargetOffset.GetSafeNormal();
	float Angle = FVector::DotProduct(ForwardVec, TargetOffset);
	float Dist = FVector::Distance(GetActorLocation(), TargetPawn->GetActorLocation());

	if (Angle >= 0.85f && Dist <= AttackDistance) 
	{ 
		return true; 
	}

	return false;
}

void ABaseMonster::ComboAttack()
{
}

float ABaseMonster::PlayAnimation(UAnimMontage * Animation, float InPlayRate, FName StartSelectName)
{
	return PlayAnimMontage(Animation, InPlayRate, StartSelectName);
}

void ABaseMonster::SetFocus()
{
	if (TargetPawn == nullptr)
		return;

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector Direction = TargetPawn->GetActorLocation() - GetActorLocation();
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

