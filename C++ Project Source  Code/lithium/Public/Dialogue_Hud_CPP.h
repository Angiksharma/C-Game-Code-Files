// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Dialogue_Hud_CPP.generated.h"

/**
 * 
 */
UCLASS()
class LITHIUM_API ADialogue_Hud_CPP : public AHUD
{
 GENERATED_BODY()
protected:
 virtual void DrawHUD() override;
 virtual void BeginPlay() override;

public:
	
 UPROPERTY(VisibleAnywhere)
 class AFather_CPP* Father;
	
};
