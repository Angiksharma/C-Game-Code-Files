// Fill out your copyright notice in the Description page of Project Settings.


#include "bridgeUp.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UbridgeUp::UbridgeUp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UbridgeUp::BeginPlay()
{
	Super::BeginPlay();

StartLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UbridgeUp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    FVector  TargetLocation = StartLocation;
	if (ShouldMove)
	{
    TargetLocation = StartLocation + MoveOffset;
    }
	FVector  CurrentLocation = GetOwner()->GetActorLocation();
	//float  Speed = FVector::Distance(CurrentLocation,TargetLocation) / Time;
	float Speed = MoveOffset.Length()/Time;
    FVector  NewLocation = FMath::VInterpConstantTo(CurrentLocation,TargetLocation,DeltaTime,Speed);
    GetOwner()->SetActorLocation(NewLocation);
    //UE_LOG(LogTemp, Display, TEXT("speed %f"),Speed);
	
	}

    void UbridgeUp::SetBridgeUP(bool NewShouldMove)
    {
		ShouldMove = NewShouldMove;
    }
