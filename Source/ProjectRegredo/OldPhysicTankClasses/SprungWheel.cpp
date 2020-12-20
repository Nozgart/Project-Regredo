// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(Constraint);

	Axie = CreateDefaultSubobject<USphereComponent>(FName("Axie"));
	Axie->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axie, FAttachmentTransformRules::KeepRelativeTransform);

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	WheelConstraint->AttachToComponent(Axie, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraint();
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AddDrivingForce();
	UE_LOG(LogTemp, Warning, TEXT("Hit on %f"), GetWorld()->GetTimeSeconds());
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!Root) { return; }
	Constraint->SetConstrainedComponents(Root, NAME_None, Cast<UPrimitiveComponent>(Axie), NAME_None);
	WheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(Axie), NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
	//UE_LOG(LogTemp, Warning, TEXT("NotNULL %s"), *GetAttachParentActor()->GetName());
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalDrivingForcePerFrame = 0;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Tick on %f"), GetWorld()->GetTimeSeconds());
}

void ASprungWheel::AddDrivingForce()
{
	Wheel->AddForce(Axie->GetForwardVector() * TotalDrivingForcePerFrame);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalDrivingForcePerFrame += ForceMagnitude;
}

