// Fill out your copyright notice in the Description page of Project Settings.


#include "BP_BTService_Health_Cpp.h"

#include "Lith_CPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBP_BTService_Health_Cpp::UBP_BTService_Health_Cpp()
{
	NodeName = TEXT("LithHealth");
}

void UBP_BTService_Health_Cpp::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (Lithium == nullptr)
	{
		return;
	}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(),Lithium->LithDead);

		

	
}
