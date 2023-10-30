// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_TaskClearBlackBoard_Value_CPP.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API UBT_TaskClearBlackBoard_Value_CPP : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBT_TaskClearBlackBoard_Value_CPP();
protected:
  	
  	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};