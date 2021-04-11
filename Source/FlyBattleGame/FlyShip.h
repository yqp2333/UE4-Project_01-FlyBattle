// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyShip.generated.h"

class USphereComponent; //������ͷ�ļ�����Ϊ�����˷ѡ�����ʱ��cpp�ڹ���
class UCameraComponent;
class USpringArmComponent;

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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LookAtCursor();
	void MoveUp(float Value);
	void MoveRight(float Value);
	void Move(float DeltaTIme);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
