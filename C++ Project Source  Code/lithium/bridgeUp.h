// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "bridgeUp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LITHIUM_API UbridgeUp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UbridgeUp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetBridgeUP(bool ShouldMove);

private:

UPROPERTY(EditAnywhere)
float Time = 0.5 ;

UPROPERTY(EditAnywhere)
FVector  MoveOffset;

UPROPERTY(EditAnywhere)
bool ShouldMove = false;

UPROPERTY(EditAnywhere)
float MoveDistance = 750;

FVector StartLocation;

};
