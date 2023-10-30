// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPoints_Cpp.h"

#include "AIController.h"
#include "CubeLithium_CPP.h"
#include "Kismet/GameplayStatics.h"

UBTTask_MoveToPoints_Cpp::UBTTask_MoveToPoints_Cpp()
{
	NodeName = TEXT("CubeCombatPoint");
}

EBTNodeResult::Type UBTTask_MoveToPoints_Cpp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Character = Cast<ACubeLithium_CPP>(OwnerComp.GetAIOwner()->GetPawn());
	auto Lithium = UGameplayStatics::GetPlayerPawn(this,0);
	if (Character != nullptr)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		Lithium->CustomTimeDilation= 1.0f;
		Character->MoveToCombatPoint();
		Character->HitPoints = 0;
		Character->DamagePoint = 0;
		FinishLatentTask(OwnerComp ,EBTNodeResult::Succeeded);
	}

    
	
	return EBTNodeResult::Succeeded;
}
