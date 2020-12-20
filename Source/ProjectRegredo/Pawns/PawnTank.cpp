// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void APawnTank::CalculateMoveInput(float Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("DeltaTimeSeconds %f"), GetWorld()->DeltaTimeSeconds);
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds,0,0);
}

void APawnTank::CalculateRotateInput(float Value)
{
	FRotator Rotation = FRotator(0, Value * RotateSpeed * GetWorld()->DeltaTimeSeconds, 0);
	RotationDirection = FQuat(Rotation);

	//UE_LOG(LogTemp,Warning,TEXT("Rotation pit: %f yaw: %f roll: %f"), Rotation.Pitch, Rotation.Yaw, Rotation.Roll);
	//UE_LOG(LogTemp, Warning, TEXT("RotationDirection x: %f y: %f z: %f w: %f"), RotationDirection.X, RotationDirection.Y, RotationDirection.Z, RotationDirection.W);
	//UE_LOG(LogTemp, Warning, TEXT("================================================="));
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	if (MoveDirection.X < 0) {
		AddActorLocalRotation(RotationDirection.Inverse(), true);
	}
	else{
		AddActorLocalRotation(RotationDirection, true);
	}
}

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawnTank::CalculateRotateInput);
}