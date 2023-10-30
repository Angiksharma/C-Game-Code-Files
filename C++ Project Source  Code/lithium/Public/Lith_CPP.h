// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Lith_CPP.generated.h"

UCLASS()
class LITHIUM_API ALith_CPP : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ALith_CPP();
	
    
	
    UPROPERTY(EditAnywhere)
    class UCameraComponent* MainCamera;

    UPROPERTY(VisibleAnywhere)
    class USpringArmComponent* SpringArm;
	


    UPROPERTY(EditAnywhere)
    class USphereComponent* CollisionSphere;


	UPROPERTY(EditAnywhere)
	UCameraComponent* CombatComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CameraAim;
	

    //UPROPERTY(VisibleAnywhere)
    //class UAIPerceptionStimuliSourceComponent* AiPerception;


    protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	
private:

    UFUNCTION()
    void MoveForward(float AxisValue);
	
    UFUNCTION()
    void MoveRight(float AxisValue);
	
    UFUNCTION()
    void CrouchFunc();
	
	UFUNCTION()
	void UnCrouchFunc();
protected:
	
	UFUNCTION()
	void Fire();
	
	UFUNCTION()
	void Aim();

	UFUNCTION()
	void FireRelesed();

	UFUNCTION()
	void AimRelesed();

	UFUNCTION()
	void SprintFunc();

	UFUNCTION()
	void NormalWalkFunc();

	

	UPROPERTY(EditAnywhere)
	class TSubclassOf<AGun_CPP> GunClass;

	UPROPERTY()
	class AGun_CPP* Gun;

	UPROPERTY(EditAnywhere)
	class UAnimSequence* FireAnim;

	UPROPERTY(EditAnywhere)
	UAnimMontage* FireMontage;
	
	UPROPERTY(EditAnywhere)
	class UAnimSequence* Death;
	
	UPROPERTY(EditAnywhere)
	class UAnimMontage* Hit;
	
  
	UFUNCTION(BlueprintPure)
	bool Isdead() const;

	UFUNCTION(BlueprintPure)
	bool CombatMode() const;


	
    UFUNCTION()
    void PickUp();
	
    UFUNCTION()
    void Talk();



	
	UFUNCTION()
	void NormalCamera();

    UFUNCTION()
    void BeginOverLap(UPrimitiveComponent* OverLappedComponent,class  AActor* OtherActor, class UPrimitiveComponent* OtherComponent,int32 OtherBodyIndex,bool bFromSweep , const FHitResult& HitResult);


	

	UPROPERTY(EditAnywhere)
	class UCharacterMovementComponent* CharacterMovements = GetCharacterMovement();

	UPROPERTY(VisibleAnywhere)
	float MaxHealth = 111.0f;

	UPROPERTY(EditAnywhere)
	FVector OriginalLocation;
	
	UPROPERTY(EditAnywhere)
	FVector TickLocation;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool GunEquipped = false;

	UPROPERTY(BlueprintReadOnly)
	bool GunWalk = false;

	UPROPERTY(BlueprintReadOnly)
	bool CrouchMode = false;

	UPROPERTY(BlueprintReadOnly)
	bool SprintMode = false;

	UPROPERTY(BlueprintReadOnly)
	bool bAim = false;

	UPROPERTY(BlueprintReadOnly)
	bool LithDead = false;
	
	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditInstanceOnly)
	float NewX = 0;


	UFUNCTION()
	void CombatCamera();
	
};