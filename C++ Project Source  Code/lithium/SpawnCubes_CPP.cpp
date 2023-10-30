// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnCubes_CPP.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ASpawnCubes_CPP::ASpawnCubes_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = Scene;

    Pointmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointMeshComp"));
    Pointmesh->SetupAttachment(Scene);

    SecondCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondCuboid"));
    SecondCube->SetupAttachment(Pointmesh);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	BoxCollision->SetupAttachment(SecondCube);
	BoxCollision->SetGenerateOverlapEvents(true);
	
	
	//BoxCollision->SetCollisionProfileName(TEXT("Pawn"));


	

}

// Called when the game starts or when spawned
void ASpawnCubes_CPP::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(4.0f);
	
}

// Called every frame
void ASpawnCubes_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

