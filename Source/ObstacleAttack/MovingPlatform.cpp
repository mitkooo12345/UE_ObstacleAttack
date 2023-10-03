// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// FVector MyVector = FVector(-14570.0,-1750.0,4000.0);	
	// SetActorLocation(MyVector);

	StartLocation = GetActorLocation();		

	UE_LOG(LogTemp, Display, TEXT("HELLO WORLD"));

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime) {

	if (ShouldPlatformReturn()) {
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MaxMoveDistance;
		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;
	} else {
		FVector CurrentLocaton = GetActorLocation();
		CurrentLocaton = CurrentLocaton + PlatformVelocity * DeltaTime;	
		SetActorLocation(CurrentLocaton);	
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime) {
	AddActorLocalRotation(Velocity * DeltaTime);
}

 bool AMovingPlatform::ShouldPlatformReturn() const {
	return GetDistanceMoved() > MaxMoveDistance;
}

 float AMovingPlatform::GetDistanceMoved() const {
	return FVector::Dist(StartLocation, GetActorLocation());
}

