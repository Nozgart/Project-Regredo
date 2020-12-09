// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTREGREDO_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CustomMoving")
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "CustomMoving")
		void IntendTurnRight(float Throw, float ThrowForward);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTrack* LeftToSet, UTankTrack* RightToSet);

private:
	//Для передвижения ИИ (или нет)
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
