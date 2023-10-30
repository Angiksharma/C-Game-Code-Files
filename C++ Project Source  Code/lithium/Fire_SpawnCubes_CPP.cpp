// Fill out your copyright notice in the Description page of Project Settings.


#include "Fire_SpawnCubes_CPP.h"

#include "Cave_Wall_CPP.h"
#include "Lith_CPP.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

AFire_SpawnCubes_CPP::AFire_SpawnCubes_CPP()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>FireMesh(TEXT("/Script/Engine.StaticMesh'/Game/MobileStarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (FireMesh.Succeeded())
	{
		SecondCube->SetStaticMesh(FireMesh.Object);
		SecondCube->BodyInstance.SetCollisionProfileName("BlockAll");
		SecondCube->SetRelativeScale3D(FVector(0.10f,0.10f,0.10f));
		ConstructorHelpers::FObjectFinder<UMaterial>FireMaterial(TEXT("/Script/Engine.Material'/Game/Vis/Shared/Materials/Black.Black'"));
		if (FireMaterial.Succeeded())
		{
			SecondCube->SetMaterial(0,FireMaterial.Object);
		}
	}
	
	BoxCollision->SetRelativeScale3D(FVector(0.25f,0.25f,0.25f));
	BoxCollision->SetupAttachment(RootComponent);
	//BoxCollision->BodyInstance.SetCollisionProfileName("ECollisionProfile::OverlapAll_ProfileName");
	BoxCollision->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	
	
	FireProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Speed"));
	FireProjectileMovement->InitialSpeed = 3000.f;
	FireProjectileMovement->MaxSpeed = 3500.f;
		
}

void AFire_SpawnCubes_CPP::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	const FName FireTag = FName (TEXT("Fire"));
	const FName Block = FName (TEXT("Block"));
	ALith_CPP* Lith = Cast<ALith_CPP>(OtherActor);
	 auto BlockWall = Cast<ACave_Wall_CPP>(OtherActor);
	const UPrimitiveComponent* HItCompBox = Cast<UBoxComponent>(OtherComp);
	HItCompBox = OtherComp;
	
	if(OtherActor == Lith)
       {
      	UGameplayStatics::ApplyDamage(OtherActor,0.1f,GetOwner()->GetInstigatorController(),this,UDamageType::StaticClass());
    
		GEngine->AddOnScreenDebugMessage(-5,2.0f,FColor::Blue,TEXT("Lithium"));
		
       }
	if (OtherActor->ActorHasTag(Block))
	{
		GEngine->AddOnScreenDebugMessage(-2,2.0f,FColor::Blue,TEXT("Block wall"));
		if (ImpactEffect)
		{
			
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location);
		}
		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(),ImpactSound,Hit.Location);
		}
		
		
	//	if (this)
		//{
			//this->Destroy(true);
		//}
		
	}
}

void AFire_SpawnCubes_CPP::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentHit.AddDynamic(this,&AFire_SpawnCubes_CPP::OnCompHit);
	SetLifeSpan(5.0f);
}





