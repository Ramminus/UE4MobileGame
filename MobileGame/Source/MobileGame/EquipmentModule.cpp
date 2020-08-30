// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentModule.h"
#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "MobileGameCharacter.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UEquipmentModule::UEquipmentModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	
	// ...
}

void UEquipmentModule::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UEquipmentModule, CurrentWeapon);
	
}

void UEquipmentModule::EquipWeapon(TSubclassOf<UWeapon> NewWeapon) {

	
	if(GetOwnerRole() == ROLE_AutonomousProxy)
	{
		ServerEquipWeapon(NewWeapon);
		return;
	}
	else if(GetOwnerRole() == ROLE_Authority)
	{
		CurrentWeapon = NewWeapon.GetDefaultObject();
		CurrentWeapon->OwnerTeam = Cast<AMobileGameCharacter>(GetOwner())->GetTeam();
		WeaponMesh->SetSkeletalMesh(CurrentWeapon->GetModel());
		OnEquipWeapon.Broadcast();
	}
}

// Called when the game starts
void UEquipmentModule::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipmentModule::OnUpdateWeapon()
{
	WeaponMesh->SetSkeletalMesh(CurrentWeapon->GetModel());
	OnEquipWeapon.Broadcast();
	
}


void UEquipmentModule::ServerEquipWeapon_Implementation(TSubclassOf<UWeapon> WeaponToEquip)
{
	EquipWeapon(WeaponToEquip);	
}


// Called every frame
void UEquipmentModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

