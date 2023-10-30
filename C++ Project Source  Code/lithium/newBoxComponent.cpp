// Fill out your copyright notice in the Description page of Project Settings.


#include "newBoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

UnewBoxComponent::UnewBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UnewBoxComponent::BeginPlay()

{
	Super::BeginPlay();
	
}

void UnewBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* ReturnActor = AcceptableActorTag();
    if (ReturnActor != nullptr)
    
    {
      UPrimitiveComponent* Components = Cast<UPrimitiveComponent>(ReturnActor->GetRootComponent());
      if (Components != nullptr)
      {
         Components->SetSimulatePhysics(false);
        
      }

     //ReturnActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
      
      
       bridgeup->SetBridgeUP(true);
      
    }

    //else 
    //{
      //  bridgeup->SetBridgeUP(false);
       // UE_LOG(LogTemp, Display, TEXT("locking"));
        
   // }
    

    
    

    //if (Actors.Num() > 0)
    //{
       // FString ActorName = Actors[0]->GetActorNameOrLabel();
       // UE_LOG(LogTemp, Display, TEXT("Overlapping: %s"), *ActorName);
    //}

   //int32 index = 0;

   //while (index < Actors.Num())
   //{

    //FString Name = Actors[index]->GetActorNameOrLabel();
    //UE_LOG(LogTemp, Display, TEXT("Name: %s"),*Name);

    //++index;
   //}

   //for (int32 i = 0; i < Actors.Num(); i++)
   //{
    //FString Name = Actors[i]->GetActorNameOrLabel();
    //UE_LOG(LogTemp, Display, TEXT("Name: %s"),*Name);
   //}
  

}

void UnewBoxComponent::SetBridgeUp(UbridgeUp* NewBridgeup)

{
  bridgeup = NewBridgeup; 
}

AActor* UnewBoxComponent::AcceptableActorTag() const

{

TArray<AActor*> Actors;
GetOverlappingActors(Actors);
for (AActor* Actor : Actors)
{


bool UnlockTag =  Actor->ActorHasTag("Unlock");
bool Grabbed = Actor->ActorHasTag("Grabbed");
if (UnlockTag && !Grabbed)

{
return Actor;
}
     
}

return nullptr;

}

