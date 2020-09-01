// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

class IInteractable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOBILEGAME_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();
	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	TScriptInterface<IInteractable> CurrentInteractable;
private:
	

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Set the current interactable
	UFUNCTION(BlueprintCallable, Category="Interaction")
	bool SetCurrentInteractable(TScriptInterface<IInteractable> NewInteractable);
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ClearCurrentInteractable(TScriptInterface<IInteractable> InteractableToClear, const bool bEvenIfNotEquals = false);
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact();
		
};
