// Fill out your copyright notice in the Description page of Project Settings.


#include "AGun_CPP.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Lith_CPP.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values

AGun_CPP::AGun_CPP()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(Root);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>GunAsset(TEXT("/Script/Engine.StaticMesh'/Game/asses/SM_Rifle_01.SM_Rifle_01'"));
	if (GunAsset.Succeeded())
	{
		
		GunMesh->SetStaticMesh(GunAsset.Object);
    	
    	
	}

	MainCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MainSphere"));
	MainCollision->SetupAttachment(GunMesh);
	MainCollision->InitSphereRadius(59.0f);
	Aim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunAim"));
	Aim->SetupAttachment(Root);
}

void AGun_CPP::BeginPlay()
{
	Super::BeginPlay();
}

void AGun_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AGun_CPP::PullTrigger()
{
	FVector SizeParticles = FVector(10.f,10.f,10.f); 
	UGameplayStatics::SpawnEmitterAttached(FireParticles,GunMesh,TEXT("muzzle"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),FireSound,GunMesh->GetSocketLocation("muzzle"));
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)return;
	AController* OwnerController = OwnerPawn->GetController();
	
	if (OwnerController == nullptr)return;
	
	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location,Rotation);
	
	FVector End = Location + Rotation.Vector() * MaxRange;
	
	// TODO: LineTrace
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel12,Params);
	if (bSuccess)
	{
	//	DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, false);
		FVector SpawnPoint = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,SpawnPoint.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),BulletHitSound,Hit.Location);
		AActor* HitActor = Hit.GetActor();
		auto LithActor = Cast<ALith_CPP>(HitActor);
		if (HitActor != nullptr && HitActor!= LithActor)
		{
			
			AActor* DamageHitActor = Hit.GetActor();
			if (DamageHitActor != nullptr)
			{
			//	DrawDebugCamera(GetWorld(),Location,Rotation,90.0f,2,FColor::Red,true);
				FPointDamageEvent DamageEvent(Damage,Hit,SpawnPoint,nullptr);
				DamageHitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
			}
			
		}
		
	}

	//
	
}
