// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyShip.generated.h"

class USphereComponent; //不引用头文件，因为会有浪费。报错时在cpp融过来
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

	UPROPERTY(VisibleAnywhere, Category = "Component")//使组件在blueprint中显示，Visible只能被看到，而edit可以被编辑
	UStaticMeshComponent* shipSM;//声明材质

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* CollisionComp; //声明碰撞体

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp; //声明摄像机

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
