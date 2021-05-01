// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FlyShip.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShipGameModeBase.h"
#include "EnemySpawner.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateAbstractDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));
	ShipSM->SetupAttachment(RootComponent);

	Speed = 300;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	FlyShip = Cast<AFlyShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	SetColor();
	FlyShipGameMode = Cast<AShipGameModeBase>(UGameplayStatics::GetGameMode(this));
	TArray<AActor*> EnemySpawnerArray;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), EnemySpawnerArray);
	EnemySpawner = Cast<AEnemySpawner>(EnemySpawnerArray[0]);
}

void AEnemy::MoveTowardsPlayer(float DeltaTime)
{
	FVector Direct = (FlyShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	AddActorWorldOffset(Direct*Speed* DeltaTime, true);
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FlyShip->GetActorLocation()));
}

void AEnemy::OnDeath()
{
	FlyShipGameMode->IncreaseScore();
	EnemySpawner->DecreaseEnemyCount();
	SpawExplorsion();
	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!FlyShip->GetIsDead())
	{
		MoveTowardsPlayer(DeltaTime);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

