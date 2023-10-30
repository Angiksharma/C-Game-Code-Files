// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enemy_HealthComponent_CPP.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LITHIUM_API UEnemy_HealthComponent_CPP : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemy_HealthComponent_CPP();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere,Category="Health")
	float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere,Category="Health")
	float Health = 100.0f;
	UPROPERTY(EditAnywhere)
	class ACubeLithium_CPP* CubeLithium;

	//UFUNCTION()
	//void DamageTaken(float DamageAmount, FDamageEvent const& DamageType, class AController* InstigatedBy,
	//AActor* DamageCauser);
	UFUNCTION()
	void DamageTaken(AActor*DamagedActor,float DamageAmount,const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

		
};
