// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "lithium/Father_CPP.h"
#include "Text_Widgit_Excescise.generated.h"

UCLASS()
class LITHIUM_API UText_Widgit_Excescise : public UUserWidget
{
	GENERATED_BODY()

	
protected:
	
	
	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UTextBlock* Message_1;

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UTextBlock* Message_2;

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UTextBlock* Exit_Text;
	
	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Button_0;
	
	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Button_1;
	
	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Exit_Button;
	


	UPROPERTY(VisibleAnywhere)
	int32 Dialogues;


	
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnClicked1();

	UFUNCTION()
	void OnClicked2();

	UFUNCTION()
	void Exit1();

public:

	UPROPERTY(meta = (BindWidget))
	bool bExit = false;

	UPROPERTY(VisibleAnywhere)
	class AFather_CPP* Father;
	

	UPROPERTY(VisibleAnywhere)
	class ACubeLithium_CPP* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class APlayerController* MyController;

	

	
	

	
	
};
