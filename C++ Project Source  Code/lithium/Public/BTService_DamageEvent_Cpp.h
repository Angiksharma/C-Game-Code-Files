// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DamageEvent_Cpp.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API UBTService_DamageEvent_Cpp : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_DamageEvent_Cpp();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
