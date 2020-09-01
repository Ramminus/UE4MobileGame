// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableNPC.h"
#include "InteractComponent.h"
#include "Components/SphereComponent.h"

class UInteractComponent;
// Sets default values
AInteractableNPC::AInteractableNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Collider"));
	InteractCollider->SetupAttachment(RootComponent);
	InteractCollider->OnComponentBeginOverlap.AddDynamic(this, &AInteractableNPC::OnOverlapBegin);
	InteractCollider->OnComponentEndOverlap.AddDynamic(this, &AInteractableNPC::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AInteractableNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableNPC::OnInteract_Implementation()
{
	bInteracted = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Inteacted"));
	
}

void AInteractableNPC::OnExitInteraction_Implementation()
{
	bInteracted = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Stopped Inteacting"));
}

void AInteractableNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UInteractComponent* InteractComponent = Cast<UInteractComponent>( OtherActor->GetComponentByClass(UInteractComponent::StaticClass()));
	if(InteractComponent != nullptr)
	{
		const bool bSet = InteractComponent->SetCurrentInteractable(this);
		if(bSet)
		{
			Interactor = OtherActor;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Set Interaction"));
		}
		
	}
}

void AInteractableNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == Interactor)
	{
		Cast<UInteractComponent>(Interactor->GetComponentByClass(UInteractComponent::StaticClass()))->ClearCurrentInteractable(this);
		if(bInteracted)
		{
			OnExitInteraction();
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Cleared"));
	}
}

void AInteractableNPC::SetHasInteracted(bool bHasInteracted)
{
	bInteracted = bHasInteracted;
}


