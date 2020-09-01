// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueEvent.h"
#include "DialogueController.generated.h"

struct FDialogue;
USTRUCT(Blueprintable)
struct FSentenceReplace
{
	GENERATED_BODY()


		UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FName PlayerName;


};

UCLASS()
class MOBILEGAME_API ADialogueController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueController();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Dialogue")
	FSentenceReplace SentenceReplace;
private:
	int CurrentSentenceIndex;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Current Dialogue
	UPROPERTY(BlueprintGetter=GetCurrentDialogue)
	FDialogue CurrentDialogue;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	//Initialize a new dialogue in game.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Dialogue")
	void InitializeNewDialogue(FDialogue Dialogue);
	virtual void InitializeNewDialogue_Implementation(FDialogue Dialogue);

	//Current Dialogue Getter.
	UFUNCTION(BlueprintGetter, Category = "Dialogue")
	FORCEINLINE FDialogue GetCurrentDialogue() const {return CurrentDialogue;}
	
};


