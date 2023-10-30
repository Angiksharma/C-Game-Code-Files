// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOvingBridge1.generated.h"

UCLASS()
class LITHIUM_API AMOvingBridge1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMOvingBridge1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
//private:

UPROPERTY(EditAnywhere, Category = "MOvingBridge1")
FVector PlatformVelocity = FVector(40,0,0);
UPROPERTY(EditAnywhere, Category = "MOvingBridge1")
float MoveDistance = 100;

UPROPERTY(EditAnywhere , Category = "MOvingBridge1")
FRotator RotationVelocity = FRotator (0,70,0);

FVector StartLocation;

void ShouldPlatformMove(float DeltaTime);
void ShouldPlatformRotate(float Deltatime);

bool ShouldPlatformReturn() ;


};
