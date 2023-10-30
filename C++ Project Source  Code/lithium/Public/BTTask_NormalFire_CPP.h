// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_NormalFire_CPP.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API UBTTask_NormalFire_CPP : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_NormalFire_CPP();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

};
