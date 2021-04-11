// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyShip.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"



// Sets default values

AFlyShip::AFlyShip() //��ʼʱ���ã���Ҫ���ڸ�ֵ�����캯����
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	shipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));//ʵ����
	shipSM-> SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp ->SetupAttachment(SpringArmComp);

	Speed = 2500;
}

// Called when the game starts or when spawned
void AFlyShip::BeginPlay() //��ʼʱ����һ�Σ�������
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController()); 
	PC->bShowMouseCursor = true;//��ʾ���
	
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
	AddMovementInput(FVector::ForwardVector,Value);
}

void AFlyShip::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

void AFlyShip::Move(float DeltaTIme)
{
	AddActorWorldOffset(ConsumeMovementInputVector() *Speed * DeltaTIme, true);
}

// Called every frame
void AFlyShip::Tick(float DeltaTime)//ÿһִ֡��
{
	Super::Tick(DeltaTime);
	LookAtCursor();
	Move(DeltaTime);
}

// Called to bind functionality to input
void AFlyShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &AFlyShip::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFlyShip::MoveRight);

}

