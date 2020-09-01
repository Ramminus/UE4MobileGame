// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include  "Interactable.h"
// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInteractComponent::SetCurrentInteractable(TScriptInterface<IInteractable> NewInteractable)
{
	//Only set it if the current interactable is null;
	if(CurrentInteractable != nullptr) return false;
	CurrentInteractable = NewInteractable;
	
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Cyan, "Set Interactable");
	return true;
}

void UInteractComponent::ClearCurrentInteractable(TScriptInterface<IInteractable> InteractableToClear,
	const bool bEvenIfNotEquals)
{
	if(InteractableToClear == CurrentInteractable || bEvenIfNotEquals){
		CurrentInteractable = nullptr;
	}
}

void UInteractComponent::Interact()
{
	if(CurrentInteractable.GetObjectRef() == nullptr) return;
	IInteractable::Execute_OnInteract(CurrentInteractable.GetObjectRef());
}

