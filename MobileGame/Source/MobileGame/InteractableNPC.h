// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "InteractableNPC.generated.h"

class USphereComponent;

UCLASS()
class MOBILEGAME_API AInteractableNPC : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInteractableNPC();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	USphereComponent* InteractCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AActor* Interactor;
	UPROPERTY(BlueprintGetter=GetHasInteracted)
	bool bInteracted;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Interface Implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintNativeEvent, Category = "Interactable")
	void OnInteract();
	virtual void OnInteract_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintNativeEvent, Category = "Interactable")
	void OnExitInteraction();
	virtual void OnExitInteraction_Implementation();

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Setter And Getter for bInteracted
	UFUNCTION()
	void SetHasInteracted(bool bHasInteracted);
	UFUNCTION(BlueprintGetter, Category="Interaction")
	FORCEINLINE bool GetHasInteracted() const {return bInteracted ;}
	
};

