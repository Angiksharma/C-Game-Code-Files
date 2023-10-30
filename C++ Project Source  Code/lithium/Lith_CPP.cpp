// Fill out your copyright notice in the Description page of Project Settings.


#include "Lith_CPP.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AGun_CPP.h"

// Sets default values
ALith_CPP::ALith_CPP()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;
	
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MainCamera->SetupAttachment(SpringArm);
	MainCamera->bUsePawnControlRotation = false;

	CameraAim = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunAim"));
	CameraAim->SetupAttachment(SpringArm);
	
	CombatComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("Combat_Camera"));
	CombatComponent->SetupAttachment(GetMesh());
	CombatComponent->bUsePawnControlRotation = false;
	CombatComponent->Deactivate();

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MainSphere"));
	CollisionSphere->SetupAttachment(GetMesh());
	CollisionSphere->InitSphereRadius(10.0f);
	CollisionSphere->SetGenerateOverlapEvents(true);
	CollisionSphere->SetHiddenInGame(false);
	CollisionSphere->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this,&ALith_CPP::BeginOverLap);
	
	

	ConstructorHelpers::FObjectFinder<USkeletalMesh>MainSkull(TEXT("/Script/Engine.SkeletalMesh'/Game/lithium/lithium/reallithium.reallithium'"));
	if (MainSkull.Succeeded())
	{
		
		   GetMesh()->SetSkeletalMeshAsset(MainSkull.Object);
		   GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		   GetMesh()->SetRelativeLocation(FVector(1.0f,1.0f,-90.0f));
		   GetMesh()->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
		   GetMesh()->SetRelativeScale3D(FVector(10.0f,10.0f,10.0f));
	}
	
	
	static ConstructorHelpers::FObjectFinder<UAnimSequence>Fire(TEXT("/Script/Engine.AnimSequence'/Game/lithium/lithium/fire1.fire1'"));
	FireAnim = Fire.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage>FireMon(TEXT("/Script/Engine.AnimMontage'/Game/lithium/lithium/fire1montage.fire1montage'"));
	FireMontage = FireMon.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage>HitAnim(TEXT("/Script/Engine.AnimMontage'/Game/lithium/lithium/hitwhilerifle.hitwhilerifle'"));
	Hit = HitAnim.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimSequence>DeathAnim(TEXT("/Script/Engine.AnimSequence'/Game/lithium/lithium/Crouch_Death_Anim.Crouch_Death_Anim'"));
	Death = DeathAnim.Object;
	
	
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	

}

void ALith_CPP::BeginPlay()
{
	Super::BeginPlay();
	PickUp();
	Health = MaxHealth;
	OriginalLocation = MainCamera->GetComponentLocation();
    
	
}

void ALith_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

void ALith_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"),this,&ALith_CPP::MoveForward);
	PlayerInputComponent->BindAction(TEXT("NormalCamera"),IE_Pressed,this,&ALith_CPP::NormalCamera);
	PlayerInputComponent->BindAction(TEXT("CameraMode"),IE_Pressed,this,&ALith_CPP::CombatCamera);
	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"),this,&ALith_CPP::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightC++"),this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("fire"), EInputEvent::IE_Pressed, this, &ALith_CPP::Fire);
	PlayerInputComponent->BindAction(TEXT("fire"), EInputEvent::IE_Released, this, &ALith_CPP::FireRelesed);
	PlayerInputComponent->BindAction(TEXT("walkaim"), EInputEvent::IE_Pressed, this, &ALith_CPP::Aim);
	PlayerInputComponent->BindAction(TEXT("walkaim"), EInputEvent::IE_Released, this, &ALith_CPP::AimRelesed);
	PlayerInputComponent->BindAction(TEXT("combat mode stealth"), EInputEvent::IE_Pressed, this, &ALith_CPP::CrouchFunc);
	PlayerInputComponent->BindAction(TEXT("combat mode stealth"), EInputEvent::IE_Released, this, &ALith_CPP::UnCrouchFunc);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ALith_CPP::SprintFunc);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ALith_CPP::NormalWalkFunc);
}

float ALith_CPP::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Health > 0.0f)
	{
		
        	DamageApplied = FMath::Min(Health,DamageApplied);
        	Health -=DamageApplied;
        	
		   
		
		if (FireMontage)
		{
			PlayAnimMontage(Hit);
		
			
		}
	}
	if(Health <= 0.0f)
	{
		if (Death)
		{
			GetMesh()->PlayAnimation(Death,false);
		}
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
		GetMesh()->SetSimulatePhysics(true);

		
	}
	return DamageApplied;
}

void ALith_CPP::MoveForward(float AxisValue)
{

	AddMovementInput(GetActorForwardVector()*AxisValue);
}

void ALith_CPP::MoveRight(float AxisValue)
{
	
	AddMovementInput(GetActorRightVector()*AxisValue);
}

void ALith_CPP::CrouchFunc()
{
	
		CrouchMode = true;
		CharacterMovements->MaxWalkSpeed = 170.0f;
	

}

void ALith_CPP::UnCrouchFunc()
{

		CrouchMode = false;
		CharacterMovements->MaxWalkSpeed = 170.0f;

}



void ALith_CPP::Fire()
{
	if (FireMontage && GunEquipped==true)
	{
		PlayAnimMontage(FireMontage);
		Gun->PullTrigger();
		bAim = true;
	}

	
}

void ALith_CPP::Aim()
{
	if (GunEquipped == true)
	{
		
			const float Speed = 170.0f;
        	CharacterMovements->MaxWalkSpeed = Speed;
        	bAim = true;
	}

}

void ALith_CPP::FireRelesed()
{
	if (GunEquipped == true)
	{
      bAim = true;
	}
	
	
}

void ALith_CPP::AimRelesed()
{
	if (GunEquipped == true)
	{
		bAim = false;
	}
	
}

void ALith_CPP::SprintFunc()
{
	if (GunEquipped)
	{
		SprintMode=true;
        	CharacterMovements->MaxWalkSpeed = 240.0f;
	}
	
}

void ALith_CPP::NormalWalkFunc()
{
	if (GunEquipped)
	{
			SprintMode = false;
        	CharacterMovements->MaxWalkSpeed = 170.f;
	}

}

bool ALith_CPP::Isdead() const
{
	
	return Health <= 0; 
}

bool ALith_CPP::CombatMode() const
{
	
	return true;
}

void ALith_CPP::PickUp()
{
	
	
	Gun = GetWorld()->SpawnActor<AGun_CPP>(GunClass);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("fire"));
	Gun->GunMesh->SetVisibility(false);
	Gun->SetOwner(this);
	
  
  
}

void ALith_CPP::Talk()
{
}

void ALith_CPP::CombatCamera()
{
	if (CombatComponent && MainCamera)
	{
			auto TargetLocation = CombatComponent->GetComponentLocation();
		   auto NewLocation = FMath::VInterpTo(OriginalLocation,TargetLocation,2.0,10.0f);
		   NewLocation.X = 350.0f;
		   NewLocation.Y = 0.0f;
		   NewLocation.Z = 0.0f;
		   MainCamera->SetRelativeLocation(NewLocation);
		   CameraAim->SetVisibility(true);
		   Gun->Aim->SetVisibility(false);
		   GetMesh()->SetVisibility(false);
		
	}

}

void ALith_CPP::NormalCamera()
{
	if (CombatComponent && MainCamera)
	{
		auto CurrentLocation = MainCamera->GetComponentLocation() ;
		auto NewLocation = OriginalLocation;
		NewLocation.X = 95.0f;
		NewLocation.Y = 0.0f;
		NewLocation.Z =0.0f;
		MainCamera->SetRelativeLocation(NewLocation);
		GetMesh()->SetVisibility(true);
		CameraAim->SetVisibility(true);
		Gun->Aim->SetVisibility(false);
	}
	
}



void ALith_CPP::BeginOverLap(UPrimitiveComponent* OverLappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	if (OtherActor && OtherActor != this && OtherComponent) 
	{
		
	
		auto GunActor = Cast<AGun_CPP>(OtherActor);
		

		if (OtherActor == GunActor && OtherActor)
		{
			static const FName GunVisibility = TEXT("Visible");
			AActor* HitActor = HitResult.GetActor();
			if (HitActor && HitActor->ActorHasTag(GunVisibility))
			{
			
                			Gun->GunMesh->SetVisibility(true);
                			GunEquipped = true;
                			GunWalk = true;
				            HitActor-> Destroy();
			}
		
			

			}
	
		
	}
	
}


