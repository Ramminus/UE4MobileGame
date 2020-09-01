// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackModule.h"
#include "HealthModule.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EquipmentModule.h"
#include "DrawDebugHelpers.h"
#include "Sword.h"
#include "Teamable.h"
#include "Weapon.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UAttackModule::UAttackModule()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	bHasAttacked = true;

	// ...
}




// Called when the game starts
void UAttackModule::BeginPlay()
{
	Super::BeginPlay();
	HealthModule = Cast<UHealthModule>(GetOwner()->GetComponentByClass(UHealthModule::StaticClass()));
	EquipmentModule = Cast<UEquipmentModule>(GetOwner()->GetComponentByClass(UEquipmentModule::StaticClass()));
	// ...

}






// Called every frame
void UAttackModule::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (AttackTimer > 0)
	{
		AttackTimer -= DeltaTime;
	}
	// ...
}

void UAttackModule::OnAttack()
{

	//Only server can execute this.
	if(GetOwnerRole() != ROLE_Authority)return;
	EquipmentModule->GetEquipedWeapon()->OnAttack(GetWorld(), GetOwner());
}

void UAttackModule::StartAttack()
{
	//Client logic
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		//Request to start attack to the server.
		ServerOnStartAttack();

	}
	// Server logic
	else if (GetOwnerRole() == ROLE_Authority)
	{

		//Null Checks
		if ((HealthModule == nullptr) || (HealthModule->IsDead) || EquipmentModule->GetEquipedWeapon() == nullptr)return;
		
		//Return if the Attack Timer is greater than 0
		if (AttackTimer > 0) return;

		//Set Attack Timer to Weapon Attack Speed.
		AttackTimer = EquipmentModule->GetEquipedWeapon()->GetAttackSpeed();

		//Get the Attack Delay.
		float AttackDelay = EquipmentModule->GetEquipedWeapon()->GetAttackDelay();

		//Set up the delay timer to call the OnAttack Function
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandler, this, &UAttackModule::OnAttack, AttackDelay);
		//Function to call on all clients.
		MultiCastOnStartAttack();
	}
}
void UAttackModule::ServerOnStartAttack_Implementation()
{
	StartAttack();
}


void UAttackModule::MultiCastOnStartAttack_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, EquipmentModule->GetEquipedWeapon()->GetMontage()->GetName());
	MontageMeshComponent->GetAnimInstance()->Montage_Play(EquipmentModule->GetEquipedWeapon()->GetMontage(), 1, EMontagePlayReturnType::Duration);
}
void UAttackModule::ServerOnAttack_Implementation()
{
	OnAttack();
}


