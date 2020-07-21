// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackModule.h"
#include "HealthModule.h"

// Sets default values for this component's properties
UAttackModule::UAttackModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UAttackModule::BeginPlay()
{
	Super::BeginPlay();
	HealthModule = Cast<UHealthModule>(GetOwner()->GetComponentByClass(UHealthModule::StaticClass()));
	// ...
	
}


// Called every frame
void UAttackModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackModule::OnAttack()
{
	if ((HealthModule != NULL) &&(HealthModule->IsDead))return;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack!"));
}


