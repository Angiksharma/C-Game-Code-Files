

#pragma once

//#include "CubeLithium_CPP.h"
#include "CoreMinimal.h"
#include "AIController.h"

#include "CubeAIController_CPP.generated.h"


struct FAIStimulus;

UCLASS()
class LITHIUM_API ACubeAIController_CPP : public AAIController
{
	GENERATED_BODY()

public:
	//explicit ACubeAIController_CPP(FObjectInitializer const& ObjectInitializer);
	ACubeAIController_CPP();
	

	UPROPERTY(EditAnywhere, Category = "Component")
	TSoftObjectPtr<class ALith_CPP> Lithium ;
	
	UPROPERTY(EditAnywhere, Category = "Component")
	TSoftObjectPtr<class ACubeLithium_CPP> CUbeSoft;
	

	
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor ,const FAIStimulus Stimlus);
	 
	
public:
	
	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* CubePerception;

	UPROPERTY(EditAnywhere)
	class UAISenseConfig_Sight* AiSight;
	
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviour;

	UPROPERTY(EditAnywhere)
	bool Activate = false;

	UFUNCTION()
	void OnSeeingPawn();

	

	

	
	
	
};
