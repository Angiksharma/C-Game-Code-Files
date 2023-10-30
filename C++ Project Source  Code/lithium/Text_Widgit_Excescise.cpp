// Fill out your copyright notice in the Description page of Project Settings.


#include "Text_Widgit_Excescise.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


void UText_Widgit_Excescise::NativeConstruct()
{
	Super::NativeConstruct();

	if (bExit==false)

	{


		if (Message_1)
		{
		
			Message_1->SetText(FText::FromString("Who Are You"));
		}
		if (Message_2)
		{
		
			Message_2->SetText(FText::FromString("What is Going on Here "));
		}
		if (Exit_Text)
		{
		
			Exit_Text->SetText(FText::FromString("Exit"));
		}
	
		if (Button_0)
		{
			Button_0->OnClicked.AddDynamic(this, &UText_Widgit_Excescise::OnClicked1);
		
		                    		
		}
		if (Button_1)
		{
			Button_1->OnClicked.AddDynamic(this, &UText_Widgit_Excescise::OnClicked2);
		}
	
		if (Exit_Button)
		{
			Exit_Button->OnClicked.AddDynamic(this, &UText_Widgit_Excescise::Exit1);
		}
	}
}

void UText_Widgit_Excescise::OnClicked1()
{
	
	if(Dialogues <= 0 && bExit==false)
	{
		TextLabel->SetText(FText::FromString("Im The Founder of this Lab And Head of Project Lithium"));
		Dialogues++;
	}
	
}

void UText_Widgit_Excescise::OnClicked2()
{
	
	if(Dialogues<=1 && bExit==false)
	{
		TextLabel->SetText(FText::FromString("I was working on Ai ,But it got out of my control And Took Physical Shape. Go to Upper Floor Pick Up gun Only That Can Stop This Physical Form of AI"));
		Dialogues++;
	}
	
}

void UText_Widgit_Excescise::Exit1() 
{
	if ( Dialogues<=2 && bExit==false )
	{
		APlayerController*  Controller;
		Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		Controller->SetShowMouseCursor(false);
		
		UWorld* World = GetWorld();
		bExit = true;
		this->RemoveFromParent();
	   // GEngine->AddOnScreenDebugMessage(-11,6.0f,FColor::Yellow,(TEXT("ExitFunc")));
		
		
	}
}