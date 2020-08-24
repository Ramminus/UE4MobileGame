// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentModule.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UEquipmentModule::UEquipmentModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UEquipmentModule::EquipWeapon(FWeaponData NewWeapon) {
	CurrentWeapon = NewWeapon;
}

// Called when the game starts
void UEquipmentModule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

