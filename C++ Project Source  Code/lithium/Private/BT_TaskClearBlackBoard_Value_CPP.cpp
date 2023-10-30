// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_TaskClearBlackBoard_Value_CPP.h"
#include "BehaviorTree/BlackboardComponent.h"




UBT_TaskClearBlackBoard_Value_CPP::UBT_TaskClearBlackBoard_Value_CPP()
{
	NodeName = TEXT("Clear_BlackBoard_Value");
}
EBTNodeResult::Type UBT_TaskClearBlackBoard_Value_CPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	 Super::ExecuteTask(OwnerComp, NodeMemory);
	
//	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}