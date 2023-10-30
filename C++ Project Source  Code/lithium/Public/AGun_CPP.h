// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGun_CPP.generated.h"

UCLASS()
class LITHIUM_API AGun_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere)
	 USceneComponent* Root;

	
	
protected:
	
	UPROPERTY(EditAnywhere)
	class USphereComponent* MainCollision;

	UPROPERTY(EditAnywhere)
	 UParticleSystem* FireParticles;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere)
	USoundBase* BulletHitSound;

	UPROPERTY(EditAnywhere)
	class ALith_CPP* Lith;



public:
	

	UPROPERTY(EditAnywhere)
	float Damage = 0.1;

	UPROPERTY(VisibleAnywhere)
	float MaxRange = 1000.0f;

	UFUNCTION()
	void PullTrigger();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Aim;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* GunMesh;



};