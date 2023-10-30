// Fill out your copyright notice in the Description page of Project Settings.


#include "Father_CPP.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "CubeLithium_CPP.h"
#include "Fire_SpawnCubes_CPP.h"
#include "Text_Widgit_Excescise.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimationAsset.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AFather_CPP::AFather_CPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root Component"));
	RootComponent = RootCapsule;
	RootCapsule->InitCapsuleSize(34.0f,88.0f);
	RootCapsule->CanCharacterStepUpOn = ECB_No;
	RootCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	
    

	FatherMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Main Mesh"));
	FatherMesh->SetupAttachment(RootCapsule);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(TEXT("Script/Engine.SkeletalMesh'/Game/lithium/father/Kneeling_Idle.Kneeling_Idle'"));

	if(MeshContainer.Succeeded())
	{
		FatherMesh->SetSkeletalMesh(MeshContainer.Object);
		FatherMesh->SetRelativeLocation(FVector(0.0f,0.0f,-90.0f));
		FatherMesh->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
		
		static ConstructorHelpers::FObjectFinder<UAnimSequence>LaptopAnimAsset(TEXT("/Script/Engine.AnimSequence'/Game/lithium/father/Working_On_Device_Anim.Working_On_Device_Anim'"));
	    LaptopPlayingAnimation = LaptopAnimAsset.Object;

	}

    
	BackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Back Cube"));
	BackBox->SetupAttachment(FatherMesh);
	BackBox->SetRelativeLocation(FVector(-2.0f,-70.6f,94.5f));
	BackBox->SetWorldScale3D(FVector(1.0f,1.0f,2.70f));
	BackBox->SetGenerateOverlapEvents(true);
	BackBox->SetCollisionProfileName(TEXT("Trigger"));
	BackBox->OnComponentBeginOverlap.AddDynamic(this , &AFather_CPP::OverlappedCallableFunction);
	
	


	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction Arrow"));
	Arrow->SetupAttachment(RootCapsule);

	

	TableMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Table Mesh"));
	TableMesh->SetupAttachment(FatherMesh);
    TableMesh->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	TableMesh->CanCharacterStepUpOn = ECB_No;


	LaptopMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laptop Mesh"));
	LaptopMesh->SetupAttachment(FatherMesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>LaptopAsset(TEXT("StaticMesh'/Game/AssetsvilleTown/Meshes/InteriorProps/Office/SM_Laptop_01.SM_Laptop_01'"));
	if (LaptopAsset.Object != nullptr)
	
	{
		LaptopMesh->SetStaticMesh(LaptopAsset.Object);
        LaptopMesh->SetRelativeLocation(FVector(0.299f,44.0f,40.0f));
		LaptopMesh->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
		LaptopMesh->SetWorldScale3D(FVector(1.0f,1.0f,1.0f));
	}                
	
	LaptopMesh->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	
	CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("MovementComponent"));

}

// Called when the game starts or when spawned
void AFather_CPP::BeginPlay()
{
	Super::BeginPlay();

	LaptopWork();
	
}

// Called every frame
void AFather_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void AFather_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFather_CPP::LaptopWork()
{
	if (Death != true)

	{
		
	bool Loop = true;
    FatherMesh->PlayAnimation(LaptopPlayingAnimation,Loop);

    }
	 
}

void AFather_CPP::TalkFunction()
{
	GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,(TEXT("Dialogue")));
	if (IsValid(WIdgetClass))
	{
		TextWidget = Cast<UText_Widgit_Excescise>(CreateWidget(GetWorld(),WIdgetClass));
		GEngine->AddOnScreenDebugMessage(-1,12.0f,FColor::Yellow,FString::Printf(TEXT("bool : %s"),TextWidget->bExit ? TEXT("true") : TEXT("false")));
				
				
		if (TextWidget!=nullptr && ShouldTalk == true && TextWidget->bExit==false)
		{
			APlayerController*  MyController;
			MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			MyController->SetShowMouseCursor(true);
			TextWidget->AddToViewport();
		}
		if (TextWidget->bExit==true)
		{
			ShouldTalk = false;
		}
		
	}
}

void AFather_CPP::OverlappedCallableFunction(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UPrimitiveComponent* OtherComponent = Cast<UPrimitiveComponent>(OtherComp);
	static const FName MovingPointTag = TEXT("Destroy");
	static const FName LithTalk = TEXT("Fire");
	ALith_CPP* Lith = Cast<ALith_CPP>(OtherActor);
	auto Virus = Cast<ACubeLithium_CPP>(OtherActor);
	auto Box = Cast<AFire_SpawnCubes_CPP>(OtherActor);
	
	if (OtherActor == Lith && Lith->GunEquipped==false)
	{
		TalkFunction();
	}
}

void AFather_CPP::DeathScene()
{
	if (CubeLithium)
	{
		CubeLithium->SlowTime();
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Blue,(TEXT("CubeLithiumFired")));
	
		if (FatherMesh != nullptr)
	{
			FatherMesh->SetSimulatePhysics(true);
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,(TEXT("Death of father")));
	}
		if (LaptopMesh != nullptr)
	{
		    LaptopMesh->DestroyComponent(true);
		    CubeLithium->FatherShot = true;
		    Death = true;
			this->SetLifeSpan(1.0f);
		    
		if (TableMesh != nullptr)
		{
			TableMesh->DestroyComponent(true);
		}
	}}

}


		







