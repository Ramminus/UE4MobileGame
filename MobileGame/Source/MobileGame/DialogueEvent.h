// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueEvent.generated.h"


/**
 * 
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class MOBILEGAME_API UDialogueEvent : public UObject
{
	GENERATED_BODY()

public:
	//Name of the event.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName EventName;
public:
	//Event linked to button UMG to trigger.
	UFUNCTION(BlueprintNativeEvent, Category="Dialogue")
	void OnExecuteEvent(class ADialogueController* DialogueController);
	virtual void OnExecuteEvent_Implementation(class ADialogueController* DialogueController);
	
};

USTRUCT(Blueprintable)
struct FDialogueSentence
{
	GENERATED_BODY()

public:
	//Sentence Text.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DialgoueText;
	//Events Options
	UPROPERTY(BlueprintReadWrite, Instanced, EditAnywhere, Export, NoClear)
	TArray<UDialogueEvent*> DialogueEvents;
};

USTRUCT(Blueprintable)
struct FDialogue
{
	
	GENERATED_BODY()

	//Name of the person speaking.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SpokenBy;
	//Sentences in the dialogue
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FDialogueSentence> Sentences;
};
