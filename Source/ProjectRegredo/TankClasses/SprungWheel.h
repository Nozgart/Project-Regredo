// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class PROJECTREGREDO_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupConstraint();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		USphereComponent* Wheel;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		USphereComponent* Axie;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UPhysicsConstraintComponent* Constraint;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UPhysicsConstraintComponent* WheelConstraint;

	void AddDrivingForce();

	float TotalDrivingForcePerFrame = 0.f;

};
