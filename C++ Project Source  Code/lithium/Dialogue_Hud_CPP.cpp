// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue_Hud_CPP.h"
#include "lithium/Father_CPP.h"

void ADialogue_Hud_CPP::DrawHUD()
{
	Super::DrawHUD();
	
	const FString DrawHud = FString::Printf(TEXT("Who Are You"));
	DrawText(DrawHud,FColor::Red,100,500,nullptr,3.0f,false);
	
		
		
}

void ADialogue_Hud_CPP::BeginPlay()
{
	Super::BeginPlay();
	
	
}

