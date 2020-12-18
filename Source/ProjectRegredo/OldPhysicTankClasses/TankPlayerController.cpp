// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto TankPawn = GetPawn();

	if (!ensure(TankPawn))
	{
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is %s"), *(TankPawn->GetName()));
	}
}