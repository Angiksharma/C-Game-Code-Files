// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BP_BTService_Health_Cpp.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API UBP_BTService_Health_Cpp : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBP_BTService_Health_Cpp();
	
protected:
virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	class ALith_CPP* Lithium;
	
};
