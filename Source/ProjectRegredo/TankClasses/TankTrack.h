// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

class ASprungWheel;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTREGREDO_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	UTankTrack();

	UFUNCTION(BluePrintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 4000000;

	float fDeltaTime;

private:

	TArray<USceneComponent*> GetWheels() const;
};
