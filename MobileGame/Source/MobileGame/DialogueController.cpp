// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueController.h"
#include  "DialogueEvent.h"

// Sets default values
ADialogueController::ADialogueController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADialogueController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADialogueController::InitializeNewDialogue_Implementation(FDialogue Dialogue)
{
	
	CurrentSentenceIndex = 0;
	
	FDialogue Temp = Dialogue;
	for(int i =0; i< Temp.Sentences.Num(); i++)
	{
		Temp.Sentences[i].DialgoueText = Temp.Sentences[i].DialgoueText.Replace(TEXT("{playername}"), *SentenceReplace.PlayerName.ToString());
	}
	CurrentDialogue = Temp;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, CurrentDialogue.Sentences[0].DialgoueText.Replace(TEXT("{playername}"), *SentenceReplace.PlayerName.ToString()));
	
}

// Called every frame
void ADialogueController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


