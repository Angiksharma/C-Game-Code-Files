// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LookAtActor_CPP.h"

#include "AIController.h"
#include "CubeLithium_CPP.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_LookAtActor_CPP::UBTService_LookAtActor_CPP()
{
}

void UBTService_LookAtActor_CPP::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}
	auto Character = Cast<ACubeLithium_CPP>(OwnerComp.GetAIOwner()->GetPawn());
	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr && Character)
	{
		auto TargetLookAtLocation = PlayerPawn->GetActorLocation();
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(),TargetLookAtLocation);
		Character->SetActorRotation(NewRotation);
	}
	
}
