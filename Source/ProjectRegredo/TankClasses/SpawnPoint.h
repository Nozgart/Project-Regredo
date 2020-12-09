// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

class ASprungWheel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTREGREDO_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawnPoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//AActor* GetSpawnedWheel() const { return NewActor; };

	ASprungWheel* GetSpawnedWheel();
private:

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY()
		AActor* NewActor;

};
