// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Battle_Location_CPP.generated.h"

UCLASS()
class LITHIUM_API ABattle_Location_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattle_Location_CPP();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootScene;

    UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FloorPoints;

	UPROPERTY(VisibleAnywhere)
    class UBoxComponent* FloorCollision;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* FloorPointsCollision;

	UPROPERTY(VisibleAnywhere)
	bool ColorChanged;

	UPROPERTY(VisibleAnywhere)
	class UMaterial* RedMaterial;

	UPROPERTY(VisibleAnywhere)
	class UMaterial* BaseMaterial;



	UPROPERTY(VisibleAnywhere)
	class ACubeLithium_CPP* CubeLithium;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
    UFUNCTION(BluePrintCallable)
	bool NewMaterial(); 

	UFUNCTION(BluePrintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepREsult);
	
	UPROPERTY(VisibleAnywhere)
	class AActor* LithiumBullet;







public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
