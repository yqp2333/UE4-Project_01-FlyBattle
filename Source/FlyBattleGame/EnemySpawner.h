// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemy;
class AFlyShip;
class UBoxComponent;

UCLASS()

class FLYBATTLEGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<AEnemy>Enemy;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* SpawnArea;

	FVector GetGenerateLocation();

	float MinimumDistanceToplayer = 1200.f;

	AFlyShip* FlyShip;

	void SpawnEnemy();

	FTimerHandle TimerHandle_Spawn;

	float SpawnInterval;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int MaxEnemyNum;
	int CurrentEnemyNum;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DecreaseEnemyCount();

};
