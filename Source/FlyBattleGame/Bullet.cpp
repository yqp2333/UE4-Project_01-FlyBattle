// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Engine/BlockingVolume.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	BulletSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletSM"));
	BulletSM->SetupAttachment(RootComponent);
	ProjectileMovementComp = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy) {
		Enemy->OnDeath();
		Destroy();
	}
	else if (Cast<ABlockingVolume>(OtherActor)) {
		Destroy();
	}

}

