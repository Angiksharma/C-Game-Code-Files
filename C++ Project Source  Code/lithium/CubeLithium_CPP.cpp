// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeLithium_CPP.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpawnCubes_CPP.h"
#include "Engine/World.h"

#include "Base_Moving_point.h"
#include "GameFramework/Character.h"
#include "Containers/Array.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimationAsset.h"
#include "Lith_CPP.h"
#include "TimerManager.h"
#include "Father_CPP.h"
#include "Engine/EngineTypes.h"
#include "Math/Vector.h"
#include "Battle_Location_CPP.h"
#include "Cave_Wall_CPP.h"

#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


// Sets default values
ACubeLithium_CPP::ACubeLithium_CPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Health = MaxHealth;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent=Capsule; 

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MainArrow"));
	Arrow->SetupAttachment(Capsule);

	SkeltonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skelton"));
	SkeltonMesh->SetupAttachment(Capsule);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn scene"));
	SpawnPoint->SetupAttachment(Arrow);

	SpawnBox =  CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn box"));
    SpawnBox->SetupAttachment(SpawnPoint);

	FireBox =  CreateDefaultSubobject<UBoxComponent>(TEXT("Fire box"));
    FireBox->SetupAttachment(SpawnPoint);
	FireBox->SetHiddenInGame(false);
    
	CollisionBox =  CreateDefaultSubobject<UBoxComponent>(TEXT("colide box"));
    CollisionBox->SetupAttachment(SpawnPoint);
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->SetHiddenInGame(false);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this , &ACubeLithium_CPP::OnOverlapBegin);
	
	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("MovementComponent"));
	

	static ConstructorHelpers::FObjectFinder<UAnimSequence>FireAnim(TEXT("/Script/Engine.AnimSequence'/Game/lithium/lithuimcorrected/pistol/Charge.Charge'"));
	FireAnimation = FireAnim.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimSequence>HitAnim(TEXT("/Script/Engine.AnimMontage'/Game/lithium/lithuimcorrected/pistol/Hit_montage.Hit_montage'"));
	HitAnimation = HitAnim.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimSequence>RainAnim(TEXT("/Script/Engine.AnimSequence'/Game/lithium/lithuimcorrected/pistol/Standing_1H_Magic_Attack_03.Standing_1H_Magic_Attack_03'"));
	RainAnimation = RainAnim.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimSequence>HeavyAnim(TEXT("/Script/Engine.AnimMontage'/Game/lithium/lithuimcorrected/pistol/Charge_Montage.Charge_Montage'"));
	HeavyAnimation = HeavyAnim.Object;

	const ConstructorHelpers::FObjectFinder<UMaterial>FireMaterial(TEXT("/Script/Engine.Material'/Game/Vis/Shared/Materials/HighlightMaterial_WIP.HighlightMaterial_WIP'"));
	if (FireMaterial.Succeeded())
	{
		WallMaterial=FireMaterial.Object;
	}

	Two = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TwoCubes.First"));
	Two->SetupAttachment(RootComponent);
    const ConstructorHelpers::FObjectFinder<UStaticMeshComponent>FirstCube(TEXT("/Script/Engine.StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
    if (FirstCube.Object!= nullptr)
    {
    	Two = FirstCube.Object;
    	Two->SetVisibility(true);
    }

	
	First = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TwoCubes.Second"));
	First->SetupAttachment(Two);
    const ConstructorHelpers::FObjectFinder<UStaticMeshComponent>SecondCube(TEXT("/Script/Engine.StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	if (SecondCube.Object!= nullptr)
	{
		First = SecondCube.Object;
		
		First->SetVisibility(false);
	}

	
	
}

UBehaviorTree* ACubeLithium_CPP::GetBehaviorTree() const
{

	return Tree;
}


// Called when the game starts or when spawned
void ACubeLithium_CPP::BeginPlay()
{
	Super::BeginPlay();
	//TwoCubesFun();
	
	//GetWorldTimerManager().SetTimer(Timer,this,&ACubeLithium_CPP::Fire,0.1f,true,0.6f);
	//this->OnTakeAnyDamage.AddDynamic(this, &ACubeLithium_CPP::TakeDamage);
	//GetWorldTimerManager().SetTimer(Timer,this,&ACubeLithium_CPP::TwoCubesFun,0.1f,true,1.0f);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this , &ACubeLithium_CPP::OnOverlapBegin);
}

// Called every frame
void ACubeLithium_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LithiumCode = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	if (CombatMode == false)
	{
		TwoCubesFun();
	  ACubeLithium_CPP::MoveCubeLithiumTo(DeltaTime);
	}
	
	 
	
}

// Called to bind functionality to input
void ACubeLithium_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


bool ACubeLithium_CPP::MoveCubeLithiumTo(float DeltaTime)
{
	if (LithiumCode && CombatMode == false)
	{
		float DistanceToLithium = this->GetDistanceTo(LithiumCode);	
		
		
		if (TeleportToBridge == false && FatherShot == false && BridgeCrossed == false && MoveToFather == false && CombatMode == false)
		{
			MovetoFirstPoint(DeltaTime);
			
		}
		 if (TeleportToBridge == true && FatherShot == false && BridgeCrossed == false && MoveToFather == false && CombatMode == false )
		{
			MovetoSecondPoint(DeltaTime);
		}
		 if (TeleportToBridge == true && FatherShot == false && BridgeCrossed == true && MoveToFather == false && CombatMode == false)
		{
			MovetoThirdPoint(DeltaTime);
		}
		 if (TeleportToBridge == true && FatherShot == false && BridgeCrossed == true && MoveToFather == true&& CombatMode == false )
		{
			MoveToFatherFunction(DeltaTime);
		}
	
	}
    return true;

}

void ACubeLithium_CPP::Fire()
{
	if (FireAttackActor)
	{
		int32 FireAmount = 4;
		
	for (int32 i = 0; i < FireAmount; i++)

	{
		UWorld* const World = GetWorld();

		if(World)
		{
			
			FRotator Rotation = FireBox->GetComponentRotation();
		    FVector Origin = FireBox->Bounds.Origin;
            FVector Extent = FireBox->Bounds.BoxExtent;
            FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin ,Extent);
            FActorSpawnParameters SpawnParams;
	        SpawnParams.Owner = this;
	        SpawnParams.Instigator = GetInstigator();

             SpawnedActor = World->SpawnActor<ASpawnCubes_CPP>(FireAttackActor,RandomLocation,Rotation,SpawnParams);

		}
	}
	}
}

void ACubeLithium_CPP::CubeRain()
{
	if (SummonCubes && LithiumCode)
	{
		
		int32 FireAmount = 41;
		FVector FireBoxOriginalLocation = FireBox->GetComponentLocation();
		FRotator FireBoxOriginalRotation = FireBox->GetComponentRotation();
		FVector FireBoxOriginalSize =  FireBox->GetComponentScale();
		FTransform FireBoxOriginalTransform = FireBox->GetComponentTransform();
		for (int32 i = 0; i <= 40; i++)
		{
			UWorld* const World = GetWorld();

			if(World  && i <= 40)
			{
				FVector CurrentLocation  = FireBox->GetComponentLocation();
				FVector LithiumLocation  = LithiumCode->GetActorLocation();
				FireBox->SetRelativeScale3D(FVector(1.5,4.25,1.0));
				FireBox-> SetRelativeRotation(FRotator(-90.0f,0.0f,0.0f));
				
				LithiumLocation.Z += 900.f;
				FireBox-> SetWorldLocation(LithiumLocation);
				
				FRotator Rotation = FireBox->GetComponentRotation();
				FVector Origin = FireBox->Bounds.Origin;
				FVector Extent = FireBox->Bounds.BoxExtent;
				FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin ,Extent);
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				SpawnedActor = World->SpawnActor<ASpawnCubes_CPP>(SummonCubes,RandomLocation,Rotation,SpawnParams);
                }
				 if(i >= 40)
				{
                    FireBox->SetRelativeTransform(FireBoxOriginalTransform);
					FireBox->SetWorldLocation(FireBoxOriginalLocation);
				 	FireBox->SetWorldRotation(FireBoxOriginalRotation);
		

				
			}
		}
	}
}

void ACubeLithium_CPP::HeavyCube()
{
	
	if (HeavyAttackActor)
	{
		int32 FireAmount = 1;
		
		for (int32 i = 0; i < FireAmount; i++)

		{
			UWorld* const World = GetWorld();

			if(World)
			{
			
				FRotator Rotation = FireBox->GetComponentRotation();
				FVector Origin = FireBox->Bounds.Origin;
				FVector Extent = FireBox->Bounds.BoxExtent;
				FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin ,Extent);
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				SpawnedActor = World->SpawnActor<ASpawnCubes_CPP>(HeavyAttackActor,RandomLocation,Rotation,SpawnParams);
			}
		}
	}
}

void ACubeLithium_CPP::TwoCubesFun()
{
	if (FatherShot == false && Two && First )
	{
		    bool randbool = FMath::RandBool();
        	auto RandomScale = FMath::VRand();
        	Two->SetRelativeLocation(RandomScale);
        	Two->SetRelativeScale3D(RandomScale);
        	First->SetRelativeScale3D(RandomScale);
        	SkeltonMesh->SetVisibility(false);
	}
	
}

void ACubeLithium_CPP::SlowTime()
{
	int32 SpawnNumber = 5;
for(int32 i = 0; i < SpawnNumber ; i++)

	{
		if (GetWorld())
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2);
			this->CustomTimeDilation= 0.6;
			Fire();
		}
		
		
	}
	

}

void ACubeLithium_CPP::NormalTime()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	this->CustomTimeDilation= 1.0f;
}

void ACubeLithium_CPP::NormalAnimFire()
{
	
	SkeltonMesh->PlayAnimation(FireAnimation,false);
	FTimerHandle FireHandle;
	GetWorldTimerManager().SetTimer(FireHandle,this,&ACubeLithium_CPP::Fire,0.93);
	
}

void ACubeLithium_CPP::RainAnimFire()
{
	SkeltonMesh->PlayAnimation(RainAnimation,false);
	FTimerHandle RainHandle;
	GetWorldTimerManager().SetTimer(RainHandle,this,&ACubeLithium_CPP::CubeRain,0.83);
	
}

void ACubeLithium_CPP::HeavyAnimFire()
{
	
	SkeltonMesh->PlayAnimation(HeavyAnimation,false);
	FTimerHandle RainHandle;
	GetWorldTimerManager().SetTimer(RainHandle,this,&ACubeLithium_CPP::HeavyCube,2.50);
}

void ACubeLithium_CPP::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult)
{
	static const FName LithiumTag = TEXT("LithiumTag");
	static const FName MovingPointTag = TEXT("Destroy");
	static const FName Walltag = TEXT("Wall");
	static const FName ForthTag = TEXT("Forthpoint");
	ALith_CPP* Lith = Cast<ALith_CPP>(OtherActor);
	
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	UBoxComponent* OtherComponent = Cast<UBoxComponent>(OtherComp);
	auto CaveActor = Cast<ACave_Wall_CPP>(OtherActor);
	AActor* MovingpointActors = Cast<ABase_Moving_point>(OtherActor);

	
	if(OtherActor!=this && OtherActor->ActorHasTag(Walltag))
	{
		
		OtherComp->SetMaterial(0,WallMaterial);
		OtherActor->SetLifeSpan(10.0f);
		
		OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	if (OtherActor->ActorHasTag(ForthTag))
     	{
     		bForthPoint = true;
     	}
	if (OtherActor == Lith )
	{
		SkeltonMesh->SetVisibility(true);
		
		if (Lith->GunEquipped == true && KillFather ==false && bForthPoint == false)
		{
			if (KillFather == false)
			{
				KillFather = true;
				
			}
		}
			if (KillFather == true && FatherShot == true && bForthPoint == false)
        			{
        				ACubeLithium_CPP::MoveToFinalPoint();
        				
        			}
		if (KillFather == true && FatherShot == true && bForthPoint == true)
		{
			 MoveToCombatPoint();
			Lith->CombatCamera();
		}
	}
	
	
}

void ACubeLithium_CPP::MovetoFirstPoint(float DeltaTime)

{
	
if(DestroyedPoint == 0)	
	
	{

		AActor* FirstPoint = MovingPointArray[0];

if (LithiumCode)		
		{
			float DistanceToLithium = this->GetDistanceTo(LithiumCode);
			UE_LOG(LogTemp,Display,TEXT("Distance Between Lithium And CubeLithium: %f"),DistanceToLithium);
			float DistanceToMovePoint = this->GetDistanceTo(FirstPoint);
	
	if (DistanceToLithium <= 900 && DistanceToLithium >= 200 && DistanceToMovePoint >= 7)			

			{
		        SkeltonMesh->SetVisibility(false);
		        Two->SetVisibility(true);
		        First->SetVisibility(true);
				FVector LithiumLocation = LithiumCode->GetActorLocation();
				FVector CubeLithiumLocation = this->GetActorLocation();
				FVector TargetLocation = FirstPoint->GetActorLocation();
				FVector Direction = TargetLocation - CubeLithiumLocation; 
				Direction = Direction.GetSafeNormal();
		        FVector MovingPointLocation = CubeLithiumLocation + Direction * MovingSpeeed * DeltaTime;
				SetActorLocation(MovingPointLocation);
		       
			}
	if(DistanceToLithium <= 200 &&  TeleportToBridge == false)				

 				{
		         
		            ShouldSpawn = true;
					UWorld*  World = GetWorld();
					World->DestroyActor(FirstPoint);
					DestroyedPoint++;
		            SpawnCube();
		           TeleportToBridge =true;
 				}
		}
	}
}

void ACubeLithium_CPP::MovetoSecondPoint(float Deltatime)
{
if (LithiumCode)
	
	{
	AActor* SecondMovingPoint = MovingPointArray[1];		
    float DistanceToLithium = this->GetDistanceTo(LithiumCode);
	UE_LOG(LogTemp,Display,TEXT("Distance Between Lithium And CubeLithium: %f"),DistanceToLithium);
	float DistanceToMovePoint = this->GetDistanceTo(SecondMovingPoint);

if (DistanceToMovePoint >= 7)	

	{
	Two->SetVisibility(true);
	First->SetVisibility(true);
	FVector LithiumLocation = LithiumCode->GetActorLocation();
	FVector CubeLithiumLocation = this->GetActorLocation();
	FVector TargetLocation = SecondMovingPoint->GetActorLocation();
	SetActorLocation(TargetLocation);
	
    }
 if (DistanceToLithium <= 400 && BridgeCrossed == false)	
	{
 	  
 	    ShouldSpawn = true;
 	    UWorld*  World = GetWorld();
 	    World->DestroyActor(SecondMovingPoint);
 	    DestroyedPoint++;
 	    SpawnCube();
 	    BridgeCrossed = true;
	}
	}
}


void ACubeLithium_CPP::MovetoThirdPoint(float DeltaTimeNew)
{
if (LithiumCode)			

	{
	    AActor* ThirdPoint = MovingPointArray[2];
		float DistanceToLithium = this->GetDistanceTo(LithiumCode);
		UE_LOG(LogTemp,Display,TEXT("Distance Between Lithium And CubeLithium: %f"),DistanceToLithium);
		float DistanceToMovePoint = this->GetDistanceTo(ThirdPoint);
		UE_LOG(LogTemp,Display,TEXT("Distance Between Lithium And CubeLithium: %f"),DistanceToMovePoint);
		
if (DistanceToLithium <= 300 && DistanceToLithium >= 100 && DistanceToMovePoint >= 7)
	
{
	
	FVector LithiumLocation = LithiumCode->GetActorLocation();
	FVector CubeLithiumLocation = this->GetActorLocation();
	FVector TargetLocation = ThirdPoint->GetActorLocation();
	FVector Direction = TargetLocation - CubeLithiumLocation; 
	Direction = Direction.GetSafeNormal();
	FVector MovingPointLocation = CubeLithiumLocation + Direction * MovingSpeeed * DeltaTimeNew;
	SetActorLocation(MovingPointLocation);
	
	}
	
	 if (DistanceToLithium <= 200.f && MoveToFather == false)	
    	{
	
	 	ShouldSpawn = true;
	 	UWorld*  World = GetWorld();
	 	World->DestroyActor(ThirdPoint);
	 	SpawnCube();
	 	DestroyedPoint++;
	 	MoveToFather = true;
    	    
    	}
	
	}
}



void ACubeLithium_CPP::MoveToFatherFunction(float DeltaTime)
{
	auto FatherCollisionBox = Father->BackBox;
	FVector FatherLocation = FatherCollisionBox->GetComponentLocation();
	float DistanceToLithium = this->GetDistanceTo(LithiumCode);
	if (LithiumCode &&  MoveToFather == true && FatherShot == false)
	{
		Two->SetVisibility(false);
		First->SetVisibility(false);
		FVector CurrentLocation = GetActorLocation();
	    FVector Direction = FatherLocation - CurrentLocation + FatherLocation;
		SetActorLocation(FatherLocation);
	}

	if(Father != nullptr && FatherShot == false && KillFather == true )	
	
{
	
	Two->SetVisibility(true);
	First->SetVisibility(true);
	SkeltonMesh->SetVisibility(true);
	MoveOffset.X = -150.0f;
	SetActorLocation(FatherLocation + MoveOffset);
	Father->DeathScene();	
	 
}

	
}

void ACubeLithium_CPP::MoveToFinalPoint()
{
	if (LithiumCode)
	{
		        float DistanceToLithium = this->GetDistanceTo(LithiumCode);
	            NormalTime();
	            Two->SetVisibility(false);
    		    First->SetVisibility(false);
    		    SkeltonMesh->SetVisibility(true);
    		    AActor* ForthPoint = MovingPointArray[3];
            	FVector TargetLocation = ForthPoint->GetActorLocation();
            	SetActorLocation(TargetLocation);
		        SkeltonMesh->SetVisibility(true);
		        Health = 2.0f;
		        
		         bForthPoint =true;
		        
		
	}
}

void ACubeLithium_CPP::SpawnCube()

{
	if (SummonCubes && ShouldSpawn == true)
	
	{
		UWorld* const World = GetWorld();
		
if (World)		
   {

	int32 SpawnNumber = 50;
	for(int32 i = 0; i < SpawnNumber ; i++)

    {

    FVector Origin = SpawnBox->Bounds.Origin;
    FVector Extent = SpawnBox->Bounds.BoxExtent;
    FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin ,Extent);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	
	FVector Location = SpawnPoint->GetComponentLocation();
	FRotator Rotation = SpawnBox->GetComponentRotation();
	SpawnedActor = World->SpawnActor<ASpawnCubes_CPP>(SummonCubes,RandomLocation,Rotation,SpawnParams);

	UPrimitiveComponent* PhysicsComponent = SpawnedActor->FindComponentByClass<UPrimitiveComponent>();
		PhysicsComponent->SetSimulatePhysics(true);
		UPrimitiveComponent* StaticComponent = SpawnedActor->FindComponentByClass<UStaticMeshComponent>();
		StaticComponent->SetSimulatePhysics(true);
		
   // UE_LOG(LogTemp, Warning, TEXT(" Spawning no %d " ),i);
	if(i == 49)
	{
			PhysicsComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ShouldSpawn =  false;
	 }

	 }

	 }

	 }
     }

void ACubeLithium_CPP::DeathFunc()
{
	ShouldSpawn = true;
	SpawnCube();
	SkeltonMesh->SetSimulatePhysics(true);
	SkeltonMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	if (this)
	{
		this->Destroy();
	}
	
	
}




FRotator ACubeLithium_CPP::LookAtTarget()
{
	auto TargetLookAtLocation = LithiumCode->GetActorLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(),TargetLookAtLocation);
	return NewRotation;
}



float ACubeLithium_CPP::TakeDamage(float DamageAmount, FDamageEvent const& DamageType, AController* InstigatedBy,AActor* DamageCauser)
{
	if(Health > 0)
	{
		Health -= DamageAmount;
		bool bLoopHit = false;
		SkeltonMesh->PlayAnimation(HitAnimation,bLoopHit);
		HitPoints++;
		int32 RandNumber = FMath::RandRange(4,7);
		if (DamagePoint < RandNumber )
		{
			DamagePoint++;
		}
		if (DamagePoint >= RandNumber)
		{
			HitPoints = 9;
		}

	}
	else if(Health <= 0)
	{
	
		DeathFunc();
	}
	
	return DamageAmount;
	
}


void ACubeLithium_CPP::MoveToCombatPoint()
{
	
	const auto CubeLithiumLocation = GetActorLocation();
	const int32 RandomMovingPoints = FMath::RandRange(0,2);
	const auto CombatLocation = CombatLocations[RandomMovingPoints];
	const FVector TargetLocation =  CombatLocation->FloorPoints->GetComponentLocation();
	FVector MoveDirection =   TargetLocation - CubeLithiumLocation;
	MoveDirection = MoveDirection.GetSafeNormal();
	const auto FinalLocation  = MoveDirection + TargetLocation;
	SetActorLocation(TargetLocation);
	CombatMode = true;
	


}

