// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lith_CPP.h"
#include "GameFramework/Pawn.h"
#include "Father_CPP.generated.h"

UCLASS()
class LITHIUM_API AFather_CPP : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFather_CPP();

    UPROPERTY(VisibleAnywhere,Category="CollisionComponent")
	class UCapsuleComponent* RootCapsule;
	

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
    class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere,Category="MeshComponents",BlueprintReadOnly)
    class UBoxComponent* BackBox;

	
	UPROPERTY(VisibleAnywhere,Category="MeshComponents",BlueprintReadOnly)
	class UStaticMeshComponent* LaptopMesh;

	UPROPERTY(VisibleAnywhere,Category="MeshComponents",BlueprintReadOnly)
	class UStaticMeshComponent* TableMesh;

    
	UPROPERTY(VisibleAnywhere,Category="MeshComponents",BlueprintReadOnly)
	class UCharacterMovementComponent* CharacterMovement;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,Category="MeshComponents",BlueprintReadOnly)
	class USkeletalMeshComponent* FatherMesh;

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
    bool Death = false;

	UPROPERTY(VisibleAnywhere)
	float Health = 1.0f ;

	UPROPERTY(EditAnywhere)
    class ACubeLithium_CPP* CubeLithium;

	UPROPERTY(EditAnywhere)
    TSubclassOf<ALith_CPP>  Lithium;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget>  WIdgetClass;
	
	UPROPERTY(VisibleInstanceOnly)
	class UText_Widgit_Excescise* TextWidget;
	
	
	UPROPERTY(VisibleAnywhere)
	class ADialogue_Hud_CPP* DialogueScreen;

	UPROPERTY(VisibleAnywhere)
	class UAnimSequence* LaptopPlayingAnimation;
	
	UPROPERTY(EditAnywhere);
	bool ShouldTalk = true;

    UFUNCTION(BlueprintCallable)
	void LaptopWork();
	
	UFUNCTION()
	void TalkFunction();
	

	
	UFUNCTION()
	void OverlappedCallableFunction(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	UFUNCTION()
	void DeathScene();

};

