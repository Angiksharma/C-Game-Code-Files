// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DamageEvent_Cpp.h"

#include "AIController.h"
#include "CubeLithium_CPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_DamageEvent_Cpp::UBTService_DamageEvent_Cpp()
{
}

void UBTService_DamageEvent_Cpp::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return ;
	}
    
	auto Character = Cast<ACubeLithium_CPP>(OwnerComp.GetAIOwner()->GetPawn());
	auto Lithium = UGameplayStatics::GetPlayerPawn(this,0);
	
	if (Character->Health <= 0)
	{
		Character->DeathFunc();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),true);
		
	}
	if (Character->Health > 0)
	{
		//Character->Health--;
	}
}
