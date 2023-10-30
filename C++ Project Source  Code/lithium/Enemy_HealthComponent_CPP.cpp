// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_HealthComponent_CPP.h"
#include "CubeLithium_CPP.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UEnemy_HealthComponent_CPP::UEnemy_HealthComponent_CPP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemy_HealthComponent_CPP::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UEnemy_HealthComponent_CPP::DamageTaken);
	
	
	


	
	
}


// Called every frame
void UEnemy_HealthComponent_CPP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*void UEnemy_HealthComponent_CPP::DamageTaken(float DamageAmount, FDamageEvent const& DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(DamageAmount <= 0.f) return;
	if (Health >= 0.f && GetOwner() != nullptr )
	{
		Health -= DamageAmount;
		UE_LOG(LogTemp, Warning,TEXT("Health: %f"), Health);
	}
	
	else if (Health <= 0.f && GetOwner() != nullptr )
	{
		GEngine->AddOnScreenDebugMessage(-2,5.0f,FColor::Red,TEXT("Death"));
	}
	
	
	
}*/

void UEnemy_HealthComponent_CPP::DamageTaken(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-3,5.0f,FColor::Blue,FString::Printf(TEXT("HealthPoint: %d"),Health));
	if(DamageAmount <= 0.f) return;
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning,TEXT("Health: %f"), Health);
    
	if (Health <= 0.f && CubeLithium)
	{
		//CubeLithium->Destroy();
		GEngine->AddOnScreenDebugMessage(-2,5.0f,FColor::Red,TEXT("Death"));
	}
	
}

