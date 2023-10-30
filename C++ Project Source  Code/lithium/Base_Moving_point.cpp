// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Moving_point.h"
#include "Components/BoxComponent.h"

// Sets default values
ABase_Moving_point::ABase_Moving_point()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
	
	

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = Scene;

    Pointmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointMeshComp"));
    Pointmesh->SetupAttachment(Scene);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	BoxCollision->SetupAttachment(Scene);

	

}

// Called when the game starts or when spawned
void ABase_Moving_point::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABase_Moving_point::DestroyActor(bool CanBeDestroyed)
{
    return true;
}

// Called every frame
void ABase_Moving_point::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

