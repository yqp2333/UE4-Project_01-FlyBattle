// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FlyShip.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;

	SpawnInterval = 0.5f;

	MaxEnemyNum = 20;
	CurrentEnemyNum = 0;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	FlyShip = Cast<AFlyShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn, this, &AEnemySpawner::SpawnEnemy, SpawnInterval, true, 0.0f);

}

FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance = 0;
	FVector Location;
	while (Distance < MinimumDistanceToplayer)
	{
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin,SpawnArea->Bounds.BoxExtent);
		Distance = (Location - FlyShip->GetActorLocation()).Size();
	}
	return Location;
}

void AEnemySpawner::SpawnEnemy()
{
	if (FlyShip->GetIsDead() == false && CurrentEnemyNum <= MaxEnemyNum)
	{
		FActorSpawnParameters SpawnParameters;
		GetWorld()->SpawnActor<AEnemy>(Enemy, GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);
		CurrentEnemyNum ++;
	}

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::DecreaseEnemyCount()
{
	if (CurrentEnemyNum > 0) {
		CurrentEnemyNum--;
	}
}

