// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeAIController_CPP.h"

#include "CubeLithium_CPP.h"
#include "Lith_CPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


ACubeAIController_CPP::ACubeAIController_CPP()
{

	Lithium = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	CubePerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Ai Perception"));
	AiSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Ai Sight"));
	CubePerception->ConfigureSense(*AiSight);
	CubePerception->SetDominantSense(AiSight->GetSenseImplementation());
	AiSight->SightRadius =3000.0f ;
	AiSight->LoseSightRadius = ( 3000+ 20.0f);
	AiSight->PeripheralVisionAngleDegrees = 360.0f;
	AiSight->DetectionByAffiliation.bDetectEnemies = true;
	AiSight->DetectionByAffiliation.bDetectFriendlies = true;
	AiSight->DetectionByAffiliation.bDetectNeutrals = true;

	CubePerception->OnTargetPerceptionUpdated.AddDynamic(this,&ACubeAIController_CPP::OnPerceptionUpdated);
}

void ACubeAIController_CPP::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviour!=nullptr && GetPawn())
	{
		RunBehaviorTree(AIBehaviour);
		
		//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
		
	}
	
	
}

void ACubeAIController_CPP::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ACubeAIController_CPP::OnPerceptionUpdated(AActor* Actor, const FAIStimulus Stimlus)
{
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	Lithium = Cast<ALith_CPP>(Actor);
	if (Lithium )
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsBool(TEXT("Random Location"),CUbeSoft->RandomCombatPoints);
		GetBlackboardComponent()->SetValueAsInt(TEXT("HitPoints"),CUbeSoft->HitPoints);
		GetBlackboardComponent()->SetValueAsInt(TEXT("DamagePoint"),CUbeSoft->DamagePoint);
		GetBlackboardComponent()->SetValueAsObject(TEXT("lithActor"),PlayerPawn);
		GetBlackboardComponent()->SetValueAsFloat(TEXT("Virus Health"),CUbeSoft->Health);
		GetBlackboardComponent()->SetValueAsFloat(TEXT("Lith Health"),Lithium->Health);
		GetBlackboardComponent()->SetValueAsBool(TEXT("Combat Begin"),CUbeSoft->CombatMode);
		OnSeeingPawn();
		
	
	}
}

void ACubeAIController_CPP::OnSeeingPawn()
{
	if (GetAIPerceptionComponent()!=nullptr)
	{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "I see you!");
	
	}
}


void ACubeAIController_CPP::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	
	
	
	
}
