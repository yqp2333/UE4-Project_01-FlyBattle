// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class FLYBATTLEGAME_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* BulletSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
