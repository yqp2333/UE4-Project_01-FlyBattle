// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bullet.h"
#include "FlyShip.generated.h"


class USphereComponent; //������ͷ�ļ�����Ϊ�����˷ѡ�����ʱ��cpp�ڹ���
class UCameraComponent;
class USpringArmComponent;
class UParticleSystemComponent;
class USoundCue;
class ABullet;

UCLASS()
class FLYBATTLEGAME_API AFlyShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlyShip();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")//ʹ�����blueprint����ʾ��Visibleֻ�ܱ���������edit���Ա��༭
	UStaticMeshComponent* shipSM;//��������

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* CollisionComp; //������ײ��

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp; //���������

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;

	APlayerController* PC;

	UPROPERTY(EditAnywhere, Category="Move")
	float Speed;	

	FTimerHandle TimerHandle_BetweenShoot;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float TimeBetweenFire;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<ABullet> Bullet;

	FTimerHandle TimerHandle_Restart;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* GameOverCue;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* ThrusterParticleComp;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ExplorsionParticle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isDead;
	bool isUpMove;
	bool isRightMove;
	void LookAtCursor();
	void MoveUp(float Value);
	void MoveRight(float Value);
	void Move(float DeltaTIme);
	void Fire();
	void StartFire();
	void EndFire();
	void RestartLevel();
	void OnDeath();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FORCEINLINE bool GetIsDead() {
		return isDead;
	}
};
