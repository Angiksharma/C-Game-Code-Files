// Fill out your copyright notice in the Description page of Project Settings.


#include "MOvingBridge1.h"
#include "Logging/LogVerbosity.h"

// Sets default values
AMOvingBridge1::AMOvingBridge1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMOvingBridge1::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	
}

// Called every frame
void AMOvingBridge1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShouldPlatformMove(DeltaTime);
	ShouldPlatformRotate(DeltaTime);
	




}

void AMOvingBridge1::ShouldPlatformMove(float DeltaTime)
{
	
	if (ShouldPlatformReturn())
	{
    FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    StartLocation = StartLocation + MoveDirection * MoveDistance; 
    SetActorLocation(StartLocation);
    PlatformVelocity = -PlatformVelocity;
	}

	else

	{
    FVector currentLocation = GetActorLocation(); 
	currentLocation = currentLocation + (PlatformVelocity*DeltaTime);
	SetActorLocation(currentLocation); 
	}
}

void AMOvingBridge1::ShouldPlatformRotate(float Deltatime)
{
	//FRotator CurrentRotation = GetActorRotation();
	//CurrentRotation = CurrentRotation + RotationVelocity * Deltatime;
	//SetActorRotation(CurrentRotation);
	AddActorLocalRotation(RotationVelocity * Deltatime);

}

bool AMOvingBridge1::ShouldPlatformReturn()

{

float DistanceMoved = FVector::Dist(StartLocation,GetActorLocation());
return  DistanceMoved > MoveDistance ;

}

