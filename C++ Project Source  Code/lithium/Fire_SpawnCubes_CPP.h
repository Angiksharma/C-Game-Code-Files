// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnCubes_CPP.h"
#include "Fire_SpawnCubes_CPP.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API AFire_SpawnCubes_CPP : public ASpawnCubes_CPP
{
	GENERATED_BODY()

	public:

	AFire_SpawnCubes_CPP();

	
	

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* FireProjectileMovement;

	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* ImpactSound;
	
	UFUNCTION(BlueprintCallable)
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);
	
	
};
