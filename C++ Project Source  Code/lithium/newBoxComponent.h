// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "bridgeUp.h"
#include "newBoxComponent.generated.h"

/**
 * 
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LITHIUM_API UnewBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UnewBoxComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	

void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) ;

UFUNCTION(BlueprintCallable)
void SetBridgeUp(UbridgeUp* bridgeup);



private:

UPROPERTY(EditAnywhere)
FName ActorHasTag;

AActor* AcceptableActorTag() const;


UbridgeUp* bridgeup;


};
