// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Moving_point.generated.h"

UCLASS()
class LITHIUM_API ABase_Moving_point : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Moving_point();


    
   UPROPERTY(EditAnywhere,BlueprintReadOnly)
   USceneComponent* Scene;

   UPROPERTY(EditAnywhere,BlueprintReadOnly)
   class UBoxComponent* BoxCollision;

   UPROPERTY(EditAnywhere,BlueprintReadOnly)
   class UStaticMeshComponent* Pointmesh;

    
	
	

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable,Category="Destruction")
	bool DestroyActor(bool CanBeDestroyed);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
