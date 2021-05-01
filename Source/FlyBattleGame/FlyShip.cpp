// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyShip.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Bullet.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"



// Sets default values

AFlyShip::AFlyShip() //开始时调用，主要用于赋值（构造函数）
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	shipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));//实例化
	shipSM-> SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp ->SetupAttachment(SpringArmComp);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint ->SetupAttachment(shipSM);

	ThrusterParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ThrusterParticle"));
	ThrusterParticleComp ->SetupAttachment(RootComponent);

	Speed = 2500;
	TimeBetweenFire = 0.2f;

	isDead = false;
}

// Called when the game starts or when spawned
void AFlyShip::BeginPlay() //开始时调用一次，获得类等
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController()); 
	PC->bShowMouseCursor = true;//显示鼠标
	
}

void AFlyShip::LookAtCursor() 
{
	FVector MouseLocation, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);
	FRotator Rotator =  UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	SetActorRotation(Rotator);
}

void AFlyShip::MoveUp(float Value)
{
	if (Value!=0)
	{
		isUpMove = true;
	}
	else 
	{
		isUpMove = false;
	}
	AddMovementInput(FVector::ForwardVector,Value);
}

void AFlyShip::MoveRight(float Value)
{
	if (Value != 0)
	{
		isRightMove = true;
	}
	else
	{
		isRightMove = false;
	}
	AddMovementInput(FVector::RightVector, Value);
}

void AFlyShip::Move(float DeltaTIme)
{
	AddActorWorldOffset(ConsumeMovementInputVector() *Speed * DeltaTIme, true);
}

void AFlyShip::Fire()
{
	if (Bullet&&isDead == false)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParams);
		UGameplayStatics::PlaySoundAtLocation(this, ShootCue, GetActorLocation());
	}
}

void AFlyShip::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShoot, this, &AFlyShip::Fire, TimeBetweenFire, true, 0.0f);

}

void AFlyShip::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShoot);
}

void AFlyShip::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, "MainMap");
}

void AFlyShip::OnDeath()
{
	CollisionComp->SetVisibility(false, true);
	isDead = true;
	UGameplayStatics::PlaySoundAtLocation(this, GameOverCue, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplorsionParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	GetWorldTimerManager().SetTimer(TimerHandle_Restart, this, &AFlyShip::RestartLevel, 2.0f, false);
}

// Called every frame
void AFlyShip::Tick(float DeltaTime)//每一帧执行
{
	if (!isDead)
	{
		Super::Tick(DeltaTime);
		LookAtCursor();
		Move(DeltaTime);
	}
	if (isUpMove || isRightMove)
	{
		ThrusterParticleComp->Activate();
	}
	else
	{
		ThrusterParticleComp->Deactivate();
	}
}

// Called to bind functionality to input
void AFlyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &AFlyShip::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFlyShip::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFlyShip::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFlyShip::EndFire);
}

void AFlyShip::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		if (Enemy) {
			Enemy->Destroy();
			OnDeath();
		}
}

