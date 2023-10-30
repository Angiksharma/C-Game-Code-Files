// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Location_CPP.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "CubeLithium_CPP.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABattle_Location_CPP::ABattle_Location_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	RootComponent = RootScene;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(RootScene);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FloorAsset(TEXT("'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
    if(FloorAsset.Succeeded())
	{
		FloorMesh->SetStaticMesh(FloorAsset.Object);
		FloorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		FloorMesh->SetWorldScale3D(FVector(3.6f,1.75f,1.25f));
    	
	}

	BaseMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Floor Material"));
	RedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Floor Material2"));
	
	ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("'/Game/Vis/Shared/BPs/BasicAI/StarterContent/FirstPerson/FPWeapon/Meshes/BaseMaterial.BaseMaterial'"));
    if(DefaultMaterial.Succeeded())
    {
	    BaseMaterial = (DefaultMaterial.Object);
    }

	ConstructorHelpers::FObjectFinder<UMaterial>CombatMaterial(TEXT("'/Game/Vis/Shared/Materials/HighlightMaterial_red.HighlightMaterial_red'"));
	if(CombatMaterial.Succeeded())
	{
		RedMaterial = (CombatMaterial.Object);
		
	}

	

	FloorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	FloorCollision->SetupAttachment(RootScene);
	FloorCollision->SetWorldScale3D(FVector(6.0f,3.0f,3.0f));
	FloorCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	FloorCollision->OnComponentBeginOverlap.AddDynamic(this, &ABattle_Location_CPP::OnOverlapBegin);
	
	FloorPoints = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point Mesh"));
	FloorPoints->SetupAttachment(RootScene);

	ConstructorHelpers::FObjectFinder<UStaticMesh>FloorPointAsset(TEXT("'/Game/EF_Barbra/Meshes/PoolTableBall_c.PoolTableBall_c'"));
	if(FloorPointAsset.Succeeded())
	{  
      FloorPoints->SetStaticMesh(FloorPointAsset.Object);
	  FloorPoints->SetRelativeLocation(FVector(1.0f,1.0f,190.0f));
	  FloorPoints->SetWorldScale3D(FVector(5.0f,5.0f,5.0f));
	  FloorPoints->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	  
	 ConstructorHelpers::FObjectFinder<UMaterial>PointAssetMaterial(TEXT("'/Game/lithium/police/hostage/Guard_HS_V2_Body_MIC.Guard_HS_V2_Body_MIC'"));
	  if (PointAssetMaterial.Succeeded())
	  {
		FloorPoints->SetMaterial(0,PointAssetMaterial.Object);
	  }
     
	 
} 
      FloorPointsCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Point Mesh Collision"));
	  FloorPointsCollision->SetupAttachment(FloorPoints);
	  FloorPointsCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
      FloorPointsCollision->SetSphereRadius(8.0f);
}     

// Called when the game starts or when spawned
void ABattle_Location_CPP::BeginPlay()
{
	Super::BeginPlay();

	FloorMesh->SetMaterial(0,BaseMaterial);
	
}

// Called every frame
void ABattle_Location_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABattle_Location_CPP::NewMaterial()
{
	  
	FloorMesh->SetMaterial(0,RedMaterial);
	return true;
}



void ABattle_Location_CPP::OnOverlapBegin(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepREsult)
{
   if(OtherActor != this && ColorChanged == false)
   {
   	   static const FName Tag = TEXT("CC");
	   UBoxComponent* LithCubeComp = Cast<UBoxComponent>(OtherComp);   	
   	   
   	
   	if (OtherComp == LithCubeComp && LithCubeComp->ComponentHasTag(Tag))
   	{
   		NewMaterial();
   		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,(TEXT("Overlapped")));
   	}
   }
	
	
   
   
}
   	 
	  
	