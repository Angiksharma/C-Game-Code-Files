// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToPoints_Cpp.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API UBTTask_MoveToPoints_Cpp : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MoveToPoints_Cpp();
protected:
  	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	
};
