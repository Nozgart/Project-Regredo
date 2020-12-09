// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "GameFramework/Actor.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto WheelsArr = GetWheels();
	auto ForcePerWheel = ForceApplied / WheelsArr.Num();

	for (USceneComponent* Wheel : WheelsArr)
	{
	    Cast<USpawnPoint>(Wheel)->GetSpawnedWheel()->AddDrivingForce(ForcePerWheel);
	}
}

TArray<USceneComponent*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> WheelsArray;
	this->GetChildrenComponents(false, WheelsArray);
	return WheelsArray;
}

