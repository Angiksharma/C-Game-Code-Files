// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeAIController_CPP.h"
#include "Lith_CPP.h"

#include "GameFramework/Pawn.h"
#include "CubeLithium_CPP.generated.h"



UCLASS()
class LITHIUM_API ACubeLithium_CPP : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties

	ACubeLithium_CPP();
	UBehaviorTree* GetBehaviorTree() const;


	          //Actor Components
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USceneComponent* SpawnPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	class USkeletalMeshComponent* SkeltonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* FireBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;
   
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* Staticmesh;

    UPROPERTY(EditAnywhere)
	class UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Two;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* First;
	


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	




	

protected:
	////Actors

	UPROPERTY(EditAnywhere)
	UBehaviorTree* Tree;

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class ASpawnCubes_CPP> SummonCubes;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	AActor* SpawnedActor;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class ASpawnCubes_CPP> HeavyAttackActor;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<class ASpawnCubes_CPP> FireAttackActor;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class ACharacter* LithiumCode;
    
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class TSubclassOf<ALith_CPP> CharcterBPClass;
   
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	 class UBoxComponent* LithiumBoxCollision;
     
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<class ABattle_Location_CPP*>CombatLocations;
    
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<AActor*> MovingPointArray;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class AFather_CPP* Father;

	
	UPROPERTY()
	class ACubeAIController_CPP* PlayerAI;





	

	/////////////ANIMATIONS
	UPROPERTY(EditAnywhere)
	UAnimSequence* FireAnimation;
	UPROPERTY(EditAnywhere)
	UAnimSequence* RainAnimation;
	 UPROPERTY(EditAnywhere)
	UAnimSequence* HeavyAnimation;
	 UPROPERTY(EditAnywhere)
	UAnimSequence* HitAnimation;
	 UPROPERTY(VisibleAnywhere)
	 class UAnimSequence* DeathAnimation;

	

	         ///Vectors
	UPROPERTY(VisibleAnywhere)
	FTransform OriginalFireBoxTransform;


	             ///Float

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float MovingSpeeed = 400.0f;
	

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float DistanceToTarget = 500;

	UPROPERTY(VisibleAnywhere)
	int32 HidingPoint;

	UPROPERTY(VisibleAnywhere)
	bool FireCubeRain;

	UPROPERTY(VisibleAnywhere)
	bool FireBigCube;

	UPROPERTY(VisibleAnywhere)
	float MaxHealth = 0.0f;

	

	

	



       //Materials
    UPROPERTY(EditAnywhere)
	class UMaterial* WallMaterial;

	

       

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool MoveToFather = false;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool ShouldSpawn = false;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	int32 DestroyedPoint = 0;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	float Deltatime2;



	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool KillFather = false;

	UPROPERTY(EditAnywhere)
	FVector  MoveOffset;

	UPROPERTY(EditAnyWhere)
	bool  bForthPoint = false;
	


    UPROPERTY(VisibleAnywhere)
	FTimerHandle Timer ;
	
	


	
////////Function


protected:

	UFUNCTION(Blueprintcallable)
	bool MoveCubeLithiumTo(float DeltaTime);
	
	UFUNCTION(Blueprintcallable, category = "Move to points" )
	void MovetoFirstPoint(float DeltaTime);

	UFUNCTION(Blueprintcallable, category = "Move to points" )
	void MovetoSecondPoint(float DeltaTime);

	UFUNCTION(Blueprintcallable, category = "Move to points" )
	void MovetoThirdPoint(float DeltaTimeNew);

	UFUNCTION(Blueprintcallable, category = "Move to points" )
	void MoveToFatherFunction(float DeltaTime);

	UFUNCTION(Blueprintcallable, category = "Move to points" )
	void MoveToFinalPoint();

	UFUNCTION(BlueprintCallable,Category = "SpawnCube")
    void SpawnCube();

	
	
	


	
      ///Reusable Functions



	UFUNCTION(BlueprintCallable)
	FRotator LookAtTarget();

	

	UFUNCTION(Blueprintcallable,Category = "Combat")
	void Fire();
	
	UFUNCTION(Blueprintcallable,Category = "Combat")
	void CubeRain();

	UFUNCTION(Blueprintcallable,Category = "Combat")
	void HeavyCube();

public:
	
	
	UFUNCTION(BlueprintCallable)
	void TwoCubesFun();

	UFUNCTION()
	void SlowTime();

	UFUNCTION()
	void NormalTime();

	UFUNCTION(Blueprintcallable,Category = "Combat")
	void NormalAnimFire();

	UFUNCTION(Blueprintcallable,Category = "Combat")
	void RainAnimFire();

	UFUNCTION(Blueprintcallable,Category = "Combat")
	void HeavyAnimFire();
	
	UFUNCTION(BlueprintCallable)
	void MoveToCombatPoint();

	UFUNCTION(BlueprintCallable,Category = "SpawnCube")
	void DeathFunc();
	
  
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult);

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageType, class AController* InstigatedBy,AActor* DamageCauser) override;

	//Bool

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool TeleportToBridge = false;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool BridgeCrossed = false;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool FatherShot = false;

	UPROPERTY(EditAnywhere)
	bool RandomCombatPoints = false;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool RainStop = false;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool HeavyStop = false;

	

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	bool CombatMode = false;


	
	//int

	UPROPERTY(EditAnywhere)
	int32 HitPoints;

	UPROPERTY(EditAnywhere)
	int32 DamagePoint;

	///float
	///
	UPROPERTY(EditAnywhere)
	float Health = 0.0f;

};





	
	








