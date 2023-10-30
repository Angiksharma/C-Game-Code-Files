// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalFire_CPP.h"
#include "AIController.h"
#include "CubeLithium_CPP.h"
#include "Kismet/GameplayStatics.h"

UBTTask_NormalFire_CPP::UBTTask_NormalFire_CPP()
{
	NodeName = TEXT("CPP_Normal_Fire");
}




EBTNodeResult::Type UBTTask_NormalFire_CPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
    
	auto Character = Cast<ACubeLithium_CPP>(OwnerComp.GetAIOwner()->GetPawn());
	auto Lithium = UGameplayStatics::GetPlayerPawn(this,0);
	
	if (Character != nullptr )
	{
		 
		auto Index = GetSelectedBlackboardKey();
		bool RandBool = false;
		
		if(Character != nullptr && Character->HitPoints <= 8)
			
		{
			        Character->NormalTime();
			        Character->NormalAnimFire();
			        Character->HitPoints++;
			        FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		}
		
		
			else if(Character != nullptr && Character->HitPoints == 3 && RandBool == true)
            	{
				
				UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
				Lithium->CustomTimeDilation= 1.0f;
				Character->RainAnimFire();
				Character->HitPoints++;
				Character->RandomCombatPoints = true;
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
				
            	}



		
		else if (Character != nullptr && Character->HitPoints >= 9 && RandBool == false)
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.4f);
			
			
				Lithium->CustomTimeDilation= 1.0f;
				Character->HitPoints++;
				Character->HeavyAnimFire();
				Character->RandomCombatPoints = true;
				FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
			
		}
	}
	
	return EBTNodeResult::Succeeded;
}
