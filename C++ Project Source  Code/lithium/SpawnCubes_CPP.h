// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnCubes_CPP.generated.h"

UCLASS()
class LITHIUM_API ASpawnCubes_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnCubes_CPP();

protected:
   UPROPERTY(EditAnywhere,BlueprintReadOnly)
   USceneComponent* Scene;

   UPROPERTY(EditAnywhere,BlueprintReadOnly)
   class UBoxComponent* BoxCollision;

   UPROPERTY(EditAnywhere,BlueprintReadOnly)
   class UStaticMeshComponent* Pointmesh;


   UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess="true"),BlueprintReadOnly)
   class UStaticMeshComponent* SecondCube;

	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess="true"),BlueprintReadOnly)
	class UMaterial* SecondCubeMaterial;

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
