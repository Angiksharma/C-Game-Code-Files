// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"




// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())

	{
	FVector TargetLocation = GetComponentLocation() + GetForwardVector()*HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation,GetComponentRotation());
	
	}
	
	
   }



    void UGrabber::Grab()
    {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle==nullptr)
	{
		return;
	}
	
    FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector()*DrawDistance;
    DrawDebugLine(GetWorld(),Start,End,FColor::Red);
	DrawDebugSphere(GetWorld(),End,10,10,FColor::Black,false,5);


	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,Start,End,FQuat::Identity,ECC_GameTraceChannel1,Sphere);
	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor->Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
			);
	}

	else
	{
		UE_LOG(LogTemp, Display, TEXT("No actor hit"));
	}
	

    }

    void UGrabber::Release()
    {

    UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle==nullptr)
	{
		return;
	}

	
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())

	{
		AActor* GrabbedComponent = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedComponent->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
		
		
        
		

	}
	
	
    }

    UPhysicsHandleComponent *UGrabber::GetPhysicsHandle() const
    {
    return GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    }
